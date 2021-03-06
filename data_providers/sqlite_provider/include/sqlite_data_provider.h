#ifndef _SQLITE_DATA_PROVIDER_H
#define _SQLITE_DATA_PROVIDER_H

#include "IDataProvider.h"
#include <map>
#include <string>

struct sqlite3;

namespace mtr
{

class SqliteDataProvider : public IDataProvider
{
public:
    SqliteDataProvider();
    virtual ~SqliteDataProvider();
    virtual MTR_STATUS PublishData( IDataManager * const in_data_manager );
    virtual MTR_STATUS GetData( SymbolHandle const & in_symbol_handle, 
                                AttributeHandle const & in_attribute_handle, 
                                std::vector<Timestamp> const & in_dates, 
                                std::vector<std::pair<Timestamp, double> > * out_data);
    MTR_STATUS OpenDatabase( std::string in_database_name );
    MTR_STATUS ReadYahooCSVFile( std::string in_file_name );
private:
    SqliteDataProvider( SqliteDataProvider const & );
    SqliteDataProvider const & operator=( SqliteDataProvider const & );
    inline MTR_STATUS CallSqlite(int in_return_code);
    inline MTR_STATUS CallSqliteExpect(int in_return_code, int in_expected_code);
    MTR_STATUS SqlToTimestamp(std::string const & in_time, Timestamp * out_timestamp);
    MTR_STATUS TimestampToSql(std::string * out_sql, Timestamp const & in_timestamp);

    std::map<SymbolHandle, std::string> symbol_handle_map_;
    std::map<AttributeHandle, std::string> attribute_handle_map_;
    sqlite3 * database_;
};
}

#endif //_SQLITE_DATA_PROVIDER_H
