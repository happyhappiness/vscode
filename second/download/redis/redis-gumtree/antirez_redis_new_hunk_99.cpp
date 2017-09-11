    return ac;
}

redisAsyncContext *redisAsyncConnectBindWithReuse(const char *ip, int port,
                                                  const char *source_addr) {
    redisContext *c = redisConnectBindNonBlockWithReuse(ip,port,source_addr);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}

redisAsyncContext *redisAsyncConnectUnix(const char *path) {
    redisContext *c;
    redisAsyncContext *ac;
