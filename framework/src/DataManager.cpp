#include "DataManager.h"

using namespace mtr;

SymbolHandle DataManager::handle_counter_ = 1;

DataManager::DataManager() {
}
DataManager::~DataManager() {
}

MTR_STATUS DataManager::GetSymbols( std::vector<std::string> * out_symbols ) const {
    SymbolMap::const_iterator iter;
    for(iter = symbol_map_.begin(); iter != symbol_map_.end(); iter++) {
        out_symbols->push_back(iter->first);
    }
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::GetSymbolAttributes( SymbolHandle const & in_symbol_handle, std::vector<AttributeHandle> * out_attributes ) const {
    // *out_attributes = symbol_attribute_map_[in_symbol_handle];
    return MTR_STATUS_SUCCESS;
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
    symbol_attribute_map_[in_symbol_handle].push_back(in_attribute_handle);
    return MTR_STATUS_SUCCESS;
}

Handle DataManager::GenerateHandle() {
    return handle_counter_++;
}
