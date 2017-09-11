        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        return REDIS_ERR;
    }
    if (type == AF_INET) {
        if (redisSetReuseAddr(c,s) == REDIS_ERR) {
            return REDIS_ERR;
        }
    }
    return s;
}

static int redisSetBlocking(redisContext *c, int fd, int blocking) {
    int flags;

    /* Set the socket nonblocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_GETFL)");
        close(fd);
        return REDIS_ERR;
    }

