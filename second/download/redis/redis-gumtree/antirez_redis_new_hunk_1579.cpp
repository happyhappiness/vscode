 */


#include "redis.h"
#include "rdb.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "lzf.h"
#include "crc64.h"

#define ERROR(...) { \
    redisLog(REDIS_WARNING, __VA_ARGS__); \
    exit(1); \
}

