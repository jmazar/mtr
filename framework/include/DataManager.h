#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "IDataManager.h"
#include <map>
#include <list>

namespace mtr
{

class DataManager : public IDataManager
{
public:
    DataManager();
    virtual ~DataManager();

    // virtual MTR_STATUS GetDates( std::vector<tm> & out_dates );

    virtual MTR_STATUS GetSymbols( std::vector<std::string> * out_symbols ) const;
    virtual MTR_STATUS GetSymbolAttributes( SymbolHandle const & in_symbol_handle, std::vector<AttributeHandle> * out_attributes ) const;

    virtual MTR_STATUS PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle );

    // virtual MTR_STATUS PublishSymbolDates( std::string & in_symbol_name, std::vector<tm> & in_dates );
    virtual MTR_STATUS PublishAttribute( std::string const & in_symbol_name, AttributeHandle * out_symbol_attribute_handle );
    virtual MTR_STATUS PublishSymbolAttribute( SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle );
private:
    Handle        GenerateHandle();
    typedef std::map<std::string, SymbolHandle> SymbolMap;
    typedef std::map<std::string, AttributeHandle> AttributeMap;
    typedef std::map<SymbolHandle, std::list<AttributeHandle> > SymbolAttributeMap;

    SymbolMap           symbol_map_;
    AttributeMap        attribute_map_;
    SymbolAttributeMap  symbol_attribute_map_;
    static Handle handle_counter_;
};

}

#endif // DATA_MANAGER_H
