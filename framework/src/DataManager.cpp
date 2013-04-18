#include "DataManager.h"
#include "IDataProvider.h"

using namespace mtr;

SymbolHandle DataManager::handle_counter_ = 1;

DataManager::DataManager() {
}
DataManager::~DataManager() {
}

MTR_STATUS DataManager::GetDataDates(   SymbolHandle const & in_symbol_handle, 
                                        AttributeHandle const & in_attribute_handle, 
                                        std::vector<Timestamp> * out_dates) {
    out_dates->clear();
    SymbolAttributePair pair(in_symbol_handle, in_attribute_handle);
    for(std::vector<Timestamp>::const_iterator iter = timestamp_map_[pair].begin(); iter != timestamp_map_[pair].end(); iter++) {
        out_dates->push_back(*iter);
    }
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::GetSymbols( std::vector<std::pair<std::string,
                                    SymbolHandle> > * out_symbols ) const {
    SymbolMap::const_iterator iter;
    for(iter = symbol_map_.begin(); iter != symbol_map_.end(); iter++) {
        out_symbols->push_back(*iter);
    }
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::GetSymbolAttributes(    SymbolHandle const & in_symbol_handle,
                                                std::vector<AttributeHandle> * out_attributes ) {
    if( NULL == out_attributes )
        return MTR_STATUS_FAILURE;
    out_attributes->clear();
    std::list<AttributeHandle>::const_iterator iter;
    std::list<AttributeHandle> const * const attribute_handles = &symbol_attribute_map_[in_symbol_handle];
    for(iter = attribute_handles->begin(); iter != attribute_handles->end(); iter++) {
        out_attributes->push_back(*iter);
    }
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::GetData(SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates, std::vector<std::pair<Timestamp, double> > * out_data) {
    return data_provider_map_[SymbolAttributePair(in_symbol_handle, in_attribute_handle)]->GetData(in_symbol_handle, in_attribute_handle, in_dates, out_data);
}

MTR_STATUS DataManager::PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle ) {
    // Look up symbol name.
    SymbolMap::const_iterator search_iter = symbol_map_.find(in_symbol_name);
    if( search_iter == symbol_map_.end() ) {
        // If the symbol name doesn't exist, create a new handle.
        symbol_map_[in_symbol_name] = GenerateHandle();
    }
    *out_symbol_handle = symbol_map_[in_symbol_name];
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::PublishAttribute( std::string const & in_symbol_name, AttributeHandle * out_symbol_handle ) {
    // Look up symbol name.
    AttributeMap::const_iterator search_iter = attribute_map_.find(in_symbol_name);
    if( search_iter == attribute_map_.end() ) {
        // If the symbol name doesn't exist, create a new handle.
        attribute_map_[in_symbol_name] = GenerateHandle();
    }
    *out_symbol_handle = attribute_map_[in_symbol_name];
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::PublishSymbolAttribute( SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle ) {
    if( 0 == in_symbol_handle || 0 == in_attribute_handle)
        return MTR_STATUS_FAILURE;
    std::list<AttributeHandle> * attribute_handles = & symbol_attribute_map_[in_symbol_handle]; // TODO: Make this find instead of indexing directly.
    attribute_handles->push_back(in_attribute_handle);
    attribute_handles->sort();
    attribute_handles->unique();
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::PublishData( IDataProvider * const in_data_provider, SymbolHandle const & in_symbol_handle, AttributeHandle const & in_attribute_handle, std::vector<Timestamp> const & in_dates) {
    SymbolAttributePair pair(in_symbol_handle, in_attribute_handle);
    DataProviderMap::const_iterator data_search_iter = data_provider_map_.find(pair);
    if( data_search_iter == data_provider_map_.end() ) {
        data_provider_map_[pair] = in_data_provider;
    }

    for(std::vector<Timestamp>::const_iterator iter = in_dates.begin(); iter != in_dates.end(); iter++) {
        timestamp_map_[pair].push_back(*iter);
    }
    return MTR_STATUS_SUCCESS;
}

Handle DataManager::GenerateHandle() {
    return handle_counter_++;
}
