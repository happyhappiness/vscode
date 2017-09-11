
#include "redis.h"
#include <sys/uio.h>
#include <math.h>

static void setProtocolError(redisClient *c, int pos);

