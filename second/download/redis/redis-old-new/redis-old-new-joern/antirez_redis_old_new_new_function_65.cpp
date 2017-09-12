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