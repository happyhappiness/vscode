#include "redis.h"
#include <sys/uio.h>

static void setProtocolError(redisClient *c, int pos);

void *dupClientReplyValue(void *o) {
    incrRefCount((robj*)o);
    return o;
