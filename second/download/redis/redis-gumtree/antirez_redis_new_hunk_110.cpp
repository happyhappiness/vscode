
#define __MAX_MSEC (((LONG_MAX) - 999) / 1000)

static int redisContextTimeoutMsec(redisContext *c, long *result)
{
    const struct timeval *timeout = c->timeout;
    long msec = -1;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
            *result = msec;
            return REDIS_ERR;
        }

