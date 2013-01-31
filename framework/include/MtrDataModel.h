#ifndef _MTR_DATA_MODEL_H
#define _MTR_DATA_MODEL_H

#include <stdint.h>

namespace mtr {
enum MTR_STATUS
{
    MTR_STATUS_SUCCESS = 0,
    MTR_STATUS_FAILURE = 1
};

typedef uint64_t    Handle;
typedef Handle      SymbolHandle;
typedef Handle      AttributeHandle;

enum Granularity {
    YEAR = 0,
    MONTH,
    DAY,
    HOUR,
    MINUTE,
    SECOND,
    MILLISECOND
};

struct Timestamp {
    Granularity     granularity;
    uint32_t        year;
    uint32_t        month;
    uint32_t        day;
    uint32_t        hour;
    uint32_t        minute;
    uint32_t        second;
    uint32_t        millisecond;
};
}

#endif // _MTR_DATA_MODEL_H
