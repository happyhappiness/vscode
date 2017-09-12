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