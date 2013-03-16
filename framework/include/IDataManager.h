#ifndef _I_DATA_MANAGER_H
#define _I_DATA_MANAGER_H

#include <ctime>
#include <vector>
#include <string>

#include "MtrDataModel.h"


namespace mtr {
class IDataProvider;

class IDataManager {
public:
    virtual MTR_STATUS GetDataDates( SymbolHandle const & in_symbol_handle,
                                     AttributeHandle const & in_attribute_handle,
                                     std::vector<Timestamp> * out_dates ) = 0;
    virtual MTR_STATUS GetSymbols( std::vector<std::pair<std::string, SymbolHandle> > * out_symbols) const = 0;
    virtual MTR_STATUS GetSymbolAttributes( SymbolHandle const & in_symbol_handle, 
                                            std::vector<AttributeHandle> * out_attributes ) = 0; // TODO: how do I make this const?
    virtual MTR_STATUS GetData( SymbolHandle const & in_symbol_handle, 
                                AttributeHandle const & in_attribute_handle, 
                                std::vector<Timestamp> const & in_dates, 
                                std::vector<std::pair<Timestamp, double> > * out_data ) = 0;

    virtual MTR_STATUS PublishSymbol( std::string const & in_symbol_name, 
                                      SymbolHandle * out_symbol_handle ) = 0;
    virtual MTR_STATUS PublishAttribute( std::string const & in_symbol_name, 
                                         AttributeHandle * out_symbol_handle ) = 0;
    virtual MTR_STATUS PublishSymbolAttribute( SymbolHandle const & in_symbol_handle, 
                                               AttributeHandle const & in_attribute_handle ) = 0;
    virtual MTR_STATUS PublishData( IDataProvider * const in_data_provider, SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates) = 0;
};

}

#endif //_I_DATA_MANAGER
