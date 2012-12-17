#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "IDataManager.h"

namespace mtr
{

class DataManager : public IDataManager
{
public:
    DataManager();
    virtual ~DataManager();

    virtual MTR_STATUS GetDates(std::vector<tm> & out_dates);

    virtual MTR_STATUS GetSymbolNames(std::vector<std::string> & out_symbols);
    virtual MTR_STATUS GetSymbolAttributes();

    virtual MTR_STATUS PublishSymbol(std::string & in_symbol_name, std::vector<tm> & in_dates );
    virtual MTR_STATUS PublishSymbolAttribe();
private:

};

}

#endif // DATA_MANAGER_H
