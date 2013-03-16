#ifndef _SIMPLE_DATA_PROVIDER_H

#include "IDataProvider.h"

namespace mtr {
class IDataManager;

class SimpleDataProvider : public IDataProvider {
public:
    SimpleDataProvider();
    ~SimpleDataProvider();
    virtual MTR_STATUS GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates, std::vector<std::pair<Timestamp, double> > * out_data);
    virtual MTR_STATUS PublishData( IDataManager * const in_data_manager );
};

}
#endif // _SIMPLE_DATA_PROVIDER_H

