#include "sqlite_data_provider.h"
#include "sqlite3.h"

using namespace mtr;

SqliteDataProvider::SqliteDataProvider() :
    database_(NULL) {
}
SqliteDataProvider::~SqliteDataProvider() {
    if(database_)
        delete database_; // TODO why is this a warning
}

MTR_STATUS SqliteDataProvider::PublishData( IDataManager * const in_data_manager ) {
}
MTR_STATUS SqliteDataProvider::GetData( SymbolHandle const & in_symbol_handle, 
                            AttributeHandle const & in_attribute_handle, 
                            std::vector<Timestamp> const & in_dates, 
                            std::vector<std::pair<Timestamp, double> > * out_data) {
}
MTR_STATUS OpenDatabase( std::string in_database_name ) {
}
MTR_STATUS SqliteDataProvider::ReadCSVFile( std::string in_file_name ) {
}
