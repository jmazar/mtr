#ifndef _MTR_DATA_MODEL_H
#define _MTR_DATA_MODEL_H

#include <stdint.h>

namespace mtr {
enum MTR_STATUS
{
    MTR_STATUS_SUCCESS = 0,
    MTR_STATUS_FAILURE = 1,
    MTR_STATUS_SQLITE_ERROR = 2
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
    Timestamp() 
    : granularity(YEAR)
    , year(0)
    , month(0)
    , day(0)
    , hour(0)
    , minute(0)
    , second(0)
    , millisecond(0) {}

    Timestamp(Granularity in_granularity, uint32_t in_year, uint32_t in_month, uint32_t in_day, uint32_t in_hour, uint32_t in_minute, uint32_t in_second, uint32_t in_millisecond)
    : granularity(in_granularity)
    , year(in_year)
    , month(in_month)
    , day(in_day)
    , hour(in_hour)
    , minute(in_minute)
    , second(in_second)
    , millisecond(in_millisecond) {}
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
