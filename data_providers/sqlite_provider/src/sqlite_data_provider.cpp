#include "IDataManager.h"
#include "sqlite_data_provider.h"
#include "sqlite3.h"
#include <stdio.h>
#include <sstream>

using namespace mtr;

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
            unsigned char const * symbol = sqlite3_column_text(statement, 1);
            unsigned char const * date = sqlite3_column_text(statement, 2);
            double open = sqlite3_column_double(statement,3);
            double high = sqlite3_column_double(statement,4);
            double low = sqlite3_column_double(statement,4);
            double close = sqlite3_column_double(statement,5);
            double volume = sqlite3_column_double(statement,6);
            double adj_close = sqlite3_column_double(statement,7);
            SymbolHandle handle;
            in_data_manager->PublishSymbol(reinterpret_cast<char const *>(symbol), &handle);
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
