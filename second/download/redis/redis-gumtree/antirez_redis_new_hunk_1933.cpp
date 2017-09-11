}

redisAsyncContext *redisAsyncConnect(const char *ip, int port) {
    redisContext *c;
    redisAsyncContext *ac;

    c = redisConnectNonBlock(ip,port);
    if (c == NULL)
        return NULL;

    ac = redisAsyncInitialize(c);
    if (ac == NULL) {
        redisFree(c);
        return NULL;
    }

    __redisAsyncCopyError(ac);
    return ac;
}

redisAsyncContext *redisAsyncConnectBind(const char *ip, int port,
                                         const char *source_addr) {
    redisContext *c = redisConnectBindNonBlock(ip,port,source_addr);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}

redisAsyncContext *redisAsyncConnectUnix(const char *path) {
    redisContext *c;
    redisAsyncContext *ac;

    c = redisConnectUnixNonBlock(path);
    if (c == NULL)
        return NULL;

    ac = redisAsyncInitialize(c);
    if (ac == NULL) {
        redisFree(c);
        return NULL;
    }

    __redisAsyncCopyError(ac);
    return ac;
}
