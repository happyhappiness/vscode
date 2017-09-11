    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(TCP_NODELAY): %s", strerror(errno)));
        close(fd);
        return REDIS_ERR;
    }
    return REDIS_OK;
}

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

int redisContextSetTimeout(redisContext *c, struct timeval tv) {
    if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(SO_RCVTIMEO): %s", strerror(errno)));
        return REDIS_ERR;
    }
    if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv)) == -1) {
        __redisSetError(c,REDIS_ERR_IO,
            sdscatprintf(sdsempty(), "setsockopt(SO_SNDTIMEO): %s", strerror(errno)));
        return REDIS_ERR;
    }
    return REDIS_OK;
}

int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
    int s;
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_in sa;

    if ((s = redisCreateSocket(c,AF_INET)) < 0)
        return REDIS_ERR;
    if (redisSetBlocking(c,s,0) != REDIS_OK)
        return REDIS_ERR;

    sa.sin_family = AF_INET;
