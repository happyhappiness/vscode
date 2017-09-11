
#include "redis.h"
#include <sys/uio.h>

static void setProtocolError(redisClient *c, int pos);

