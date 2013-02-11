#ifndef _I_STRATEGY_H
#define _I_STRATEGY_H

#include "MtrDataModel.h"

namespace mtr {
class IDataManager;

class IStrategy {
public:
    virtual MTR_STATUS IsAvailable(IDataManager * data_manager) = 0;
    virtual MTR_STATUS Execute(Timestamp const & begin, Timestamp const & end) = 0;
    
};

}

#endif // _I_STRATEGY_H
