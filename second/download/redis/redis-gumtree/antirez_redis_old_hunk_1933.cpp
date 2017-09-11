}

redisAsyncContext *redisAsyncConnect(const char *ip, int port) {
    redisContext *c = redisConnectNonBlock(ip,port);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}

redisAsyncContext *redisAsyncConnectUnix(const char *path) {
    redisContext *c = redisConnectUnixNonBlock(path);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}
