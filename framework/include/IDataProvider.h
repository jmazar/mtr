#ifndef _I_DATA_PROVIDER_H
#define _I_DATA_PROVIDER_H

#include "MtrDataModel.h"
#include <vector>

namespace mtr {

class IDataProvider {
public:
    virtual MTR_STATUS GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates, std::vector<std::pair<Timestamp, double> > * out_data) = 0;
};

}

#endif //_I_DATA_PROVIDER_H
