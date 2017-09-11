        flags |= O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "fcntl(F_SETFL): %s", strerror(errno)));
        close(fd);
        return REDIS_ERR;
    }
