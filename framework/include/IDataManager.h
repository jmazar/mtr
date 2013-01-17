#ifndef _I_DATA_MANAGER_H
#define _I_DATA_MANAGER_H

#include <ctime>
#include <vector>
#include <string>

#include "MtrDataModel.h"

namespace mtr
{

class IDataManager
{
public:
    // virtual MTR_STATUS GetDates(std::vector<tm> & out_dates) = 0;
    // virtual MTR_STATUS PublishSymbolDates( std::string & in_symbol_name, std::vector<tm> & in_dates ) = 0;

    virtual MTR_STATUS GetSymbols(std::vector<std::string> * out_symbols) const = 0;
    virtual MTR_STATUS GetSymbolAttributes( SymbolHandle const & in_symbol_handle, std::vector<AttributeHandle> * out_attributes ) = 0;

    virtual MTR_STATUS PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle ) = 0;
    virtual MTR_STATUS PublishAttribute( std::string const & in_symbol_name, AttributeHandle * out_symbol_handle ) = 0;
    virtual MTR_STATUS PublishSymbolAttribute( SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle ) = 0;
};

}

#endif //_I_DATA_MANAGER
