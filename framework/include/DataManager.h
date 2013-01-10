#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "IDataManager.h"
#include <map>

namespace mtr
{

class DataManager : public IDataManager
{
public:
    DataManager();
    virtual ~DataManager();

    // virtual MTR_STATUS GetDates( std::vector<tm> & out_dates );

    // virtual MTR_STATUS GetSymbolNames( std::vector<std::string> & out_symbols );
    // virtual MTR_STATUS GetSymbolAttributes();

    virtual MTR_STATUS PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle );

    // virtual MTR_STATUS PublishSymbolDates( std::string & in_symbol_name, std::vector<tm> & in_dates );
    // virtual MTR_STATUS PublishSymbolAttribe();
private:
    SymbolHandle        GenerateHandle();
    typedef std::map<std::string, SymbolHandle> SymbolMap;

    SymbolMap           symbol_map_;
    static SymbolHandle handle_counter_;
};

}

#endif // DATA_MANAGER_H
