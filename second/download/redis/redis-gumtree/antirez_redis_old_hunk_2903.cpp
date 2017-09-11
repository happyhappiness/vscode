#include "redis.h"
#include <sys/uio.h>

void *dupClientReplyValue(void *o) {
    incrRefCount((robj*)o);
    return o;
