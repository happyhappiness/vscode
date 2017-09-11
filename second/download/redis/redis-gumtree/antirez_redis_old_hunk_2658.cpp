    return REDIS_OK;
}

static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
    struct timeval to;
    struct timeval *toptr = NULL;
    fd_set wfd;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        to = *timeout;
        toptr = &to;
    }

    if (errno == EINPROGRESS) {
        FD_ZERO(&wfd);
        FD_SET(fd, &wfd);

        if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
            __redisSetErrorFromErrno(c,REDIS_ERR_IO,"select(2)");
            close(fd);
            return REDIS_ERR;
        }

        if (!FD_ISSET(fd, &wfd)) {
            errno = ETIMEDOUT;
            __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
            close(fd);
