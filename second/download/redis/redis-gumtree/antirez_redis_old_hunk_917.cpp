#include "crc64.h"

#define ERROR(...) { \
    serverLog(REDIS_WARNING, __VA_ARGS__); \
    exit(1); \
}

