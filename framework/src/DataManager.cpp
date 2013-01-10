#include "DataManager.h"

using namespace mtr;

SymbolHandle DataManager::handle_counter_ = 1;

DataManager::DataManager() {
}
DataManager::~DataManager() {
}

MTR_STATUS DataManager::PublishSymbol( std::string const & in_symbol_name, SymbolHandle * out_symbol_handle ) {
    // Look up symbol name.
    SymbolMap::const_iterator search_iter = symbol_map_.find(in_symbol_name);
    if( search_iter == symbol_map_.end() ) {
        // If the symbol name doesn't exist, create a new handle.
        // TODO: Create function for generating handles.
        symbol_map_[in_symbol_name] = GenerateHandle();
    }

    *out_symbol_handle = symbol_map_[in_symbol_name];

    return MTR_STATUS_SUCCESS;
}
MTR_STATUS DataManager::PublishSymbolAttribute( std::string const & in_symbol_name, SymbolAttributeHandle * out_symbol_handle ) {
    // Look up symbol name.
    SymbolAttributeMap::const_iterator search_iter = symbol_attribute_map_.find(in_symbol_name);
    if( search_iter == symbol_attribute_map_.end() ) {
        // If the symbol name doesn't exist, create a new handle.
        // TODO: Create function for generating handles.
        symbol_attribute_map_[in_symbol_name] = GenerateHandle();
    }

    *out_symbol_handle = symbol_attribute_map_[in_symbol_name];

    return MTR_STATUS_SUCCESS;
}

Handle DataManager::GenerateHandle() {
    return handle_counter_++;
}
