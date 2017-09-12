static int redisSetNonBlock(redisContext *c, int fd) {
    int flags;

    /* Set the socket nonblocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "fcntl(F_GETFL): %s", strerror(errno)));
        close(fd);
        return REDIS_ERR;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno)));
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
}