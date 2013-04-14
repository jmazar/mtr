#include "sqlite_data_provider.h"
#include "sqlite3.h"

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
	if( SQLITE_OK == sqlite3_open(in_database_name.c_str(), &database_) ) {
        return MTR_STATUS_SUCCESS;
	}
    return MTR_STATUS_FAILURE;
}
MTR_STATUS SqliteDataProvider::ReadCSVFile( std::string in_file_name ) {
}
