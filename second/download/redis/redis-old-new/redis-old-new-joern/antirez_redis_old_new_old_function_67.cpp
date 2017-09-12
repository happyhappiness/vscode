redisAsyncContext *redisAsyncConnect(const char *ip, int port) {
    redisContext *c = redisConnectNonBlock(ip,port);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}