#include "../include/DataManager.h"

using namespace mtr;

DataManager::DataManager() {
}
DataManager::~DataManager() {
}

MTR_STATUS DataManager::GetDates( std::vector<tm> & out_dates ) {
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::GetSymbolNames( std::vector<std::string> & out_symbols ) {
    return MTR_STATUS_SUCCESS;
}
MTR_STATUS DataManager::GetSymbolAttributes() {
    return MTR_STATUS_SUCCESS;
}

MTR_STATUS DataManager::PublishSymbol( std::string & in_symbol_name ) {
    return MTR_STATUS_SUCCESS;
}
MTR_STATUS DataManager::PublishSymbolDates( std::string & in_symbol_name, std::vector<tm> & in_dates ) {
    return MTR_STATUS_SUCCESS;
}
MTR_STATUS DataManager::PublishSymbolAttribe() {
    return MTR_STATUS_SUCCESS;
}
