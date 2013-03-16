#include "sqlite_data_provider.h"
#include "sqlite3_db.h"

SqliteDataProivder::SqliteDataProivder() :
    database_(NULL) {
}
SqliteDataProivder::~SqliteDataProivder() {
    if(database_)
        delete database;
}

MTR_STATUS SqliteDataProivder::PublishData( IDataManager * const in_data_manager ) {
}
MTR_STATUS SqliteDataProivder::GetData( SymbolHandle const & in_symbol_handle, 
                            AttributeHandle const & in_attribute_handle, 
                            std::vector<Timestamp> const & in_dates, 
                            std::vector<std::pair<Timestamp, double> > * out_data) {
}
MTR_STATUS OpenDatabase( std::string in_database_name ) {
}
MTR_STATUS SqliteDataProivder::ReadCSVFile( std::string in_file_name ) {
}
