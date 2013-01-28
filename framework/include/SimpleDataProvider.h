#ifndef _SIMPLE_DATA_PROVIDER_H

#include "IDataProvider.h"

namespace mtr {

class SimpleDataProvider : public IDataProvider {
public:
    SimpleDataProvider();
    ~SimpleDataProvider();
    virtual MTR_STATUS GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<tm> const & in_dates, std::vector<std::pair<tm, double> > * out_data);
    MTR_STATUS Init();
};

}
#endif // _SIMPLE_DATA_PROVIDER_H

