static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
    struct timeval to;
    struct timeval *toptr = NULL;
    fd_set wfd;
    int err;
    socklen_t errlen;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        to = *timeout;
        toptr = &to;
    }

    if (errno == EINPROGRESS) {
        FD_ZERO(&wfd);
        FD_SET(fd, &wfd);

        if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
            __redisSetError(c,REDIS_ERR_IO,
                sdscatprintf(sdsempty(), "select(2): %s", strerror(errno)));
            close(fd);
            return REDIS_ERR;
        }

        if (!FD_ISSET(fd, &wfd)) {
            errno = ETIMEDOUT;
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(fd);
            return REDIS_ERR;
        }

        err = 0;
        errlen = sizeof(err);
        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
            __redisSetError(c,REDIS_ERR_IO,
                sdscatprintf(sdsempty(), "getsockopt(SO_ERROR): %s", strerror(errno)));
            close(fd);
            return REDIS_ERR;
        }

        if (err) {
            errno = err;
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(fd);
            return REDIS_ERR;
        }

        return REDIS_OK;
    }

    __redisSetError(c,REDIS_ERR_IO,NULL);
    close(fd);
    return REDIS_ERR;
}