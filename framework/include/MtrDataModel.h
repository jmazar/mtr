#ifndef _MTR_DATA_MODEL_H
#define _MTR_DATA_MODEL_H

#include <stdint.h>

enum MTR_STATUS
{
    MTR_STATUS_SUCCESS = 0,
    MTR_STATUS_FAILURE = 1
};

typedef uint64_t    Handle;
typedef Handle      SymbolHandle;
typedef Handle      AttributeHandle;

#endif // _MTR_DATA_MODEL_H
