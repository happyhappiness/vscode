        if (errno == EINPROGRESS && !blocking) {
            /* This is ok. */
        } else {
            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
                return REDIS_ERR;
        }
    }

    /* Reset socket to be blocking after connect(2). */
    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
        return REDIS_ERR;

    if (redisSetTcpNoDelay(c,s) != REDIS_OK)
        return REDIS_ERR;

    c->fd = s;
    c->flags |= REDIS_CONNECTED;
    return REDIS_OK;
}

int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout) {
    int s;
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_un sa;

    if ((s = redisCreateSocket(c,AF_LOCAL)) < 0)
        return REDIS_ERR;
    if (redisSetBlocking(c,s,0) != REDIS_OK)
        return REDIS_ERR;

    sa.sun_family = AF_LOCAL;
