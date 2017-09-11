    c->errstr[0] = '\0';
    c->obuf = sdsempty();
    c->reader = redisReaderCreate();
    return c;
}

void redisFree(redisContext *c) {
    if (c->fd > 0)
        close(c->fd);
    if (c->obuf != NULL)
        sdsfree(c->obuf);
    if (c->reader != NULL)
        redisReaderFree(c->reader);
    free(c);
}

/* Connect to a Redis instance. On error the field error in the returned
 * context will be set to the return value of the error function.
 * When no set of reply functions is given, the default set will be used. */
redisContext *redisConnect(const char *ip, int port) {
    redisContext *c = redisContextInit();
    c->flags |= REDIS_BLOCK;
    redisContextConnectTcp(c,ip,port,NULL);
    return c;
}

redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv) {
    redisContext *c = redisContextInit();
    c->flags |= REDIS_BLOCK;
    redisContextConnectTcp(c,ip,port,&tv);
    return c;
}

redisContext *redisConnectNonBlock(const char *ip, int port) {
    redisContext *c = redisContextInit();
    c->flags &= ~REDIS_BLOCK;
    redisContextConnectTcp(c,ip,port,NULL);
    return c;
}

redisContext *redisConnectUnix(const char *path) {
    redisContext *c = redisContextInit();
    c->flags |= REDIS_BLOCK;
    redisContextConnectUnix(c,path,NULL);
    return c;
}

redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv) {
    redisContext *c = redisContextInit();
    c->flags |= REDIS_BLOCK;
    redisContextConnectUnix(c,path,&tv);
    return c;
}

redisContext *redisConnectUnixNonBlock(const char *path) {
    redisContext *c = redisContextInit();
    c->flags &= ~REDIS_BLOCK;
    redisContextConnectUnix(c,path,NULL);
    return c;
}

/* Set read/write timeout on a blocking socket. */
int redisSetTimeout(redisContext *c, struct timeval tv) {
    if (c->flags & REDIS_BLOCK)
        return redisContextSetTimeout(c,tv);
    return REDIS_ERR;
}

/* Use this function to handle a read event on the descriptor. It will try
 * and read some bytes from the socket and feed them to the reply parser.
 *
