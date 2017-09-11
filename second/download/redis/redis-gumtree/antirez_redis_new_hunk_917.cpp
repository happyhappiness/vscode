#include "crc64.h"

#define ERROR(...) { \
    serverLog(LL_WARNING, __VA_ARGS__); \
    exit(1); \
}

