#include "IDataManager.h"
#include "sqlite_data_provider.h"
#include "sqlite3.h"
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace mtr;

std::string ATTRIBUTE_NAMES[] = { "open", "high", "low", "close", "volume", "adj_close"};
static int const NUM_ATTRIBUTE_NAMES = 6;

SqliteDataProvider::SqliteDataProvider() :
    database_(NULL) {
}
SqliteDataProvider::~SqliteDataProvider() {
    if(database_)
        sqlite3_close(database_);
}

MTR_STATUS SqliteDataProvider::PublishData( IDataManager * const in_data_manager ) {
    std::string sql = "SELECT * from yahoo_data;";
    sqlite3_stmt * statement = NULL;
    MTR_STATUS status = CallSqlite(sqlite3_prepare_v2(database_, sql.c_str(), -1, &statement, 0));
    //status = CallSqliteExpect(sqlite3_step(statement), SQLITE_ROW);
    while(1) {
        int sqlite_return = sqlite3_step(statement);
        if(SQLITE_ROW == sqlite_return) {
            char const * symbol = reinterpret_cast<char const *>(sqlite3_column_text(statement, 1));
            char const * date = reinterpret_cast<char const *>(sqlite3_column_text(statement, 2));
            double open = sqlite3_column_double(statement,3);
            double high = sqlite3_column_double(statement,4);
            double low = sqlite3_column_double(statement,4);
            double close = sqlite3_column_double(statement,5);
            double volume = sqlite3_column_double(statement,6);
            double adj_close = sqlite3_column_double(statement,7);
            SymbolHandle symbol_handle;
            in_data_manager->PublishSymbol(symbol, &symbol_handle);
            symbol_handle_map_[symbol_handle] = symbol;
            for(int i = 0; i < NUM_ATTRIBUTE_NAMES; i++) {
                AttributeHandle attribute_handle;
                in_data_manager->PublishAttribute(ATTRIBUTE_NAMES[i], &attribute_handle);
                attribute_handle_map_[attribute_handle] = ATTRIBUTE_NAMES[i];
                in_data_manager->PublishSymbolAttribute(symbol_handle, attribute_handle);
                Timestamp timestamp;
                SqlToTimestamp(date, &timestamp);
                std::vector<Timestamp> timestamps;
                timestamps.push_back(timestamp);
                in_data_manager->PublishData(this, symbol_handle, attribute_handle, timestamps);
            }

        }
        else if(SQLITE_DONE == sqlite_return) {
            break;
        }
        else {
            // Error handling...
        }
    }

    return status;
}

MTR_STATUS SqliteDataProvider::GetData( SymbolHandle const & in_symbol_handle, 
                            AttributeHandle const & in_attribute_handle, 
                            std::vector<Timestamp> const & in_dates, 
                            std::vector<std::pair<Timestamp, double> > * out_data) {
    for(std::vector<Timestamp>::const_iterator iter = in_dates.begin(); iter != in_dates.end(); iter++) {
        std::string timestamp;
        TimestampToSql(&timestamp, *iter);
        int const STR_SIZE_MAX = 16;

        std::stringstream stream;
        stream  << "SELECT "
                << attribute_handle_map_[in_attribute_handle]
                << " from yahoo_data WHERE symbol='" 
                << symbol_handle_map_[in_symbol_handle]
                << "' AND date='"
                << timestamp
                << "';";
        std::string sql = stream.str();
        sqlite3_stmt * statement = NULL;
        MTR_STATUS status = CallSqlite(sqlite3_prepare_v2(database_, sql.c_str(), -1, &statement, 0));
        while(1) {
            int sqlite_return = sqlite3_step(statement);
            if(SQLITE_ROW == sqlite_return) {
                double data = sqlite3_column_double(statement,1);
                std::pair<Timestamp,double> pair(*iter, data);
                out_data->push_back(pair);
            }
            else if(SQLITE_DONE == sqlite_return) {
                break;
            }
            else {
                // Error handling...
            }
        }
    }

    return MTR_STATUS_SUCCESS;
}

MTR_STATUS SqliteDataProvider::OpenDatabase( std::string in_database_name ) {
    if( SQLITE_OK != sqlite3_open(in_database_name.c_str(), &database_) ) 
        return MTR_STATUS_SQLITE_ERROR;
        std::string sql = "CREATE TABLE IF NOT EXISTS yahoo_data ( id INTEGER PRIMARY KEY, symbol TEXT, date TEXT, open REAL, high REAL, low REAL, close REAL, volume INTEGER, adj_close REAL );";
    return CallSqlite(sqlite3_exec(database_, sql.c_str(), NULL, 0, NULL));
}
MTR_STATUS SqliteDataProvider::ReadYahooCSVFile( std::string in_file_name ) {
    if(!database_)
        return MTR_STATUS_FAILURE;

    // for each line, insert name of stock into database
    FILE * file = fopen( in_file_name.c_str(), "r" );
    if(!file)
        return MTR_STATUS_FAILURE;
    char line[256];
    MTR_STATUS status = MTR_STATUS_SUCCESS;
    while( NULL != fgets( line, 256, file ) ) {
        size_t length = strlen( line );
        line[length - 1] = '\0'; // Removing newline
        std::string statement("INSERT INTO yahoo_data ( symbol, date, open, high, low, close, volume, adj_close ) VALUES ('");
        std::stringstream stream(line);
        std::string token;
        std::getline( stream, token, ',' );
        statement += token + "','";
        std::getline( stream, token, ',' );
        statement += token + "',";

        while( std::getline( stream, token, ',' ) ) {
            statement += token + ",";
        }
        statement = statement.substr(0, statement.size()-1); // Remove trailing ','
        statement += ");";

        status = CallSqlite(sqlite3_exec(database_, statement.c_str(), NULL, 0, NULL));

        if(MTR_STATUS_SUCCESS != status)
            return status;
    }
    return status;
}

inline MTR_STATUS SqliteDataProvider::CallSqlite(int in_return_code) {
    return CallSqliteExpect( in_return_code, SQLITE_OK );
}
inline MTR_STATUS SqliteDataProvider::CallSqliteExpect(int in_return_code, int in_expected_code) {
    if( in_return_code != in_expected_code ) {
        std::string error = sqlite3_errmsg(database_);
        if(error != "not an error") {
            printf("%s\n", error.c_str());
            return MTR_STATUS_SQLITE_ERROR;
        }
    }
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS SqliteDataProvider::SqlToTimestamp(std::string const & in_time, Timestamp * out_timestamp) {
    out_timestamp->granularity = DAY;
    std::stringstream stream (in_time);
    std::string token;
    std::getline( stream, token, '-' );
    out_timestamp->year = atoi(token.c_str());
    std::getline( stream, token, '-' );
    out_timestamp->month = atoi(token.c_str());
    std::getline( stream, token, '-' );
    out_timestamp->day = atoi(token.c_str());
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS SqliteDataProvider::TimestampToSql(std::string * out_sql, Timestamp const & in_timestamp) {
    char timestamp_string[16];
    sprintf(timestamp_string, "%d-%02d-%02d", in_timestamp.year, in_timestamp.month, in_timestamp.day);
    *out_sql = timestamp_string;
    return MTR_STATUS_SUCCESS;
}
