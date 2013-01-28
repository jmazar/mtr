#include "SimpleDataProvider.h"

using namespace mtr;

SimpleDataProvider::SimpleDataProvider() {
}

SimpleDataProvider::~SimpleDataProvider() {
}

MTR_STATUS SimpleDataProvider::GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<tm> const & in_dates, std::vector<std::pair<tm, double> > * out_data) {
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS SimpleDataProvider::Init() {
    return MTR_STATUS_SUCCESS;
}
