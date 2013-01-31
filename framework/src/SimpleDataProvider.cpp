#include "SimpleDataProvider.h"
#include "IDataManager.h"

using namespace mtr;

SimpleDataProvider::SimpleDataProvider() {
}

SimpleDataProvider::~SimpleDataProvider() {
}

MTR_STATUS SimpleDataProvider::GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<tm> const & in_dates, std::vector<std::pair<tm, double> > * out_data) const {
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS SimpleDataProvider::Init(IDataManager * const in_data_manager) {
    SymbolHandle symbol_handle;
    in_data_manager->PublishSymbol("INTC", &symbol_handle);

    AttributeHandle avg, high, low;
    in_data_manager->PublishAttribute("avg", &avg);
    in_data_manager->PublishAttribute("high", &high);
    in_data_manager->PublishAttribute("low", &low);

    in_data_manager->PublishSymbolAttribute(symbol_handle, avg);
    in_data_manager->PublishSymbolAttribute(symbol_handle, high);
    in_data_manager->PublishSymbolAttribute(symbol_handle, low);

    std::vector<Timestamp> dates;
    dates.push_back(Timestamp(DAY, 2008, 1, 1, 0, 0, 0, 0));
    in_data_manager->PublishData(this, symbol_handle, avg, dates);

    return MTR_STATUS_SUCCESS;
}
