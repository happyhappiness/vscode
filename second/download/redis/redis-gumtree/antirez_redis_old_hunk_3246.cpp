        close(fd);
        return REDIS_ERR;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno)));
        close(fd);
        return REDIS_ERR;
    }
