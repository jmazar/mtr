#ifndef _I_DATA_PROVIDER_H
#define _I_DATA_PROVIDER_H

class IDataProvider
{
public:
    virtual void GetDataAttributes(/* date, symbol */) = 0;
};

#endif //_I_DATA_PROVIDER_H
