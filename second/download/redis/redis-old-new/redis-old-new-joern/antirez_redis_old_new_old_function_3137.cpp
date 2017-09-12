int redisContextConnectTcp(redisContext *c, const char *addr, int port) {
    int s;
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_in sa;

    if ((s = redisCreateSocket(c,AF_INET)) == REDIS_ERR)
        return REDIS_ERR;
    if (!blocking && redisSetNonBlock(c,s) == REDIS_ERR)
        return REDIS_ERR;

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_aton(addr, &sa.sin_addr) == 0) {
        struct hostent *he;

        he = gethostbyname(addr);
        if (he == NULL) {
            __redisSetError(c,REDIS_ERR_OTHER,
                sdscatprintf(sdsempty(),"can't resolve: %s",addr));
            close(s);
            return REDIS_ERR;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }

    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS && !blocking) {
            /* This is ok. */
        } else {
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(s);
            return REDIS_ERR;
        }
    }

    if (redisSetTcpNoDelay(c,s) != REDIS_OK) {
        close(s);
        return REDIS_ERR;
    }

    c->fd = s;
    return REDIS_OK;
}