#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "IDataManager.h"
#include <map>
#include <list>

namespace mtr {

class DataManager : public IDataManager {
public:
    DataManager();
    virtual ~DataManager();

    virtual MTR_STATUS GetDataDates(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> * out_dates);
    virtual MTR_STATUS GetSymbols( std::vector<std::pair<std::string, SymbolHandle> > * out_symbols ) const;
    virtual MTR_STATUS GetSymbolAttributes( SymbolHandle const & in_symbol_handle, std::vector<AttributeHandle> * out_attributes );
    virtual MTR_STATUS PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle );
    virtual MTR_STATUS PublishAttribute( std::string const & in_symbol_name, AttributeHandle * out_symbol_attribute_handle );
    virtual MTR_STATUS PublishSymbolAttribute( SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle );
    virtual MTR_STATUS PublishData( IDataProvider const * const in_data_provider, SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates);
private:
    // TODO: This should be in sqlite...
    Handle        GenerateHandle();
    typedef std::map<std::string, SymbolHandle> SymbolMap;
    typedef std::map<std::string, AttributeHandle> AttributeMap;
    typedef std::map<SymbolHandle, std::list<AttributeHandle> > SymbolAttributeMap;
    typedef std::pair<SymbolHandle, AttributeHandle> SymbolAttributePair;
    typedef std::map<SymbolAttributePair, IDataProvider const *> DataProviderMap;
    typedef std::map<SymbolAttributePair, std::vector<Timestamp> > TimestampMap;

    SymbolMap           symbol_map_;
    AttributeMap        attribute_map_;
    SymbolAttributeMap  symbol_attribute_map_;
    DataProviderMap     data_provider_map_;
    TimestampMap        timestamp_map_;
    static Handle handle_counter_;
};

}

#endif // DATA_MANAGER_H
