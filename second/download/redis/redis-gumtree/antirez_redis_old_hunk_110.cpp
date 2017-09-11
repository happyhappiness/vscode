
#define __MAX_MSEC (((LONG_MAX) - 999) / 1000)

static int redisContextWaitReady(redisContext *c, const struct timeval *timeout) {
    struct pollfd   wfd[1];
    long msec;

    msec          = -1;
    wfd[0].fd     = c->fd;
    wfd[0].events = POLLOUT;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
            __redisSetErrorFromErrno(c, REDIS_ERR_IO, NULL);
            redisContextCloseFd(c);
            return REDIS_ERR;
        }

