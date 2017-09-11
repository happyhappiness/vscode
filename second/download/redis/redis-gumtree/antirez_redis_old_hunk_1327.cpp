#include "crc64.h"

#define ERROR(...) { \
    redisLog(REDIS_WARNING, __VA_ARGS__); \
    exit(1); \
}

