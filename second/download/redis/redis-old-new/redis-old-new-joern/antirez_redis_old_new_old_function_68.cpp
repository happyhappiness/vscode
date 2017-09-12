redisAsyncContext *redisAsyncConnectUnix(const char *path) {
    redisContext *c = redisConnectUnixNonBlock(path);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}