/* We want the error field to be accessible directly instead of requiring
 * an indirection to the redisContext struct. */
static void __redisAsyncCopyError(redisAsyncContext *ac) {
    if (!ac)
        return;

    redisContext *c = &(ac->c);
    ac->err = c->err;
    ac->errstr = c->errstr;
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

int redisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn) {
    if (ac->onConnect == NULL) {
        ac->onConnect = fn;
