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
}
MTR_STATUS SqliteDataProvider::GetData( SymbolHandle const & in_symbol_handle, 
                            AttributeHandle const & in_attribute_handle, 
                            std::vector<Timestamp> const & in_dates, 
                            std::vector<std::pair<Timestamp, double> > * out_data) {
}
MTR_STATUS SqliteDataProvider::OpenDatabase( std::string in_database_name ) {
    MTR_STATUS status = MTR_STATUS_SUCCESS;
    if( SQLITE_OK != sqlite3_open(in_database_name.c_str(), &database_) ) 
        return MTR_STATUS_SQLITE_ERROR;
    status = ExecuteStatement("CREATE TABLE IF NOT EXISTS yahoo_data ( id INTEGER PRIMARY KEY, symbol TEXT, date TEXT, open REAL, high REAL, low REAL, close REAL, volume INTEGER, adj_close REAL );");
    if( MTR_STATUS_SUCCESS != status )
        return status;
    return status;
}
MTR_STATUS SqliteDataProvider::ReadYahooCSVFile( std::string in_file_name ) {
    if(!database_)
        return MTR_STATUS_FAILURE;

    // for each line, insert name of stock into database
    FILE * file = NULL;
    file = fopen( in_file_name.c_str(), "r" );
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

        printf("%s\n", statement.c_str());
        status = ExecuteStatement(statement);
        if(MTR_STATUS_SUCCESS != status)
            return status;
    }
    return status;
}

MTR_STATUS SqliteDataProvider::ExecuteStatement( std::string const & in_statement) {
    if(!database_)
        return MTR_STATUS_SQLITE_ERROR;
    int returnCode = 0;
    sqlite3_stmt * statement = NULL;
    returnCode = sqlite3_prepare_v2(database_, in_statement.c_str(), -1, &statement, 0);
    if(SQLITE_OK == returnCode) {
        sqlite3_step(statement);
    }
    else {
        std::string error = sqlite3_errmsg(database_);
        if(error != "not an error") {
            printf("%s\n", error.c_str());
            return MTR_STATUS_SQLITE_ERROR;
        }
    }

    sqlite3_finalize(statement); // TODO Error check here?

    return MTR_STATUS_SUCCESS;
}
