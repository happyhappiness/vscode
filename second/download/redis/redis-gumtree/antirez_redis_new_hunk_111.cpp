static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
                                   const struct timeval *timeout,
                                   const char *source_addr) {
    int s, rv, n;
    char _port[6];  /* strlen("65535"); */
    struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
    int blocking = (c->flags & REDIS_BLOCK);
    int reuseaddr = (c->flags & REDIS_REUSEADDR);
    int reuses = 0;
    long timeout_msec = -1;

    servinfo = NULL;
    c->connection_type = REDIS_CONN_TCP;
    c->tcp.port = port;

    /* We need to take possession of the passed parameters
     * to make them reusable for a reconnect.
     * We also carefully check we don't free data we already own,
     * as in the case of the reconnect method.
     *
     * This is a bit ugly, but atleast it works and doesn't leak memory.
     **/
    if (c->tcp.host != addr) {
        if (c->tcp.host)
            free(c->tcp.host);

        c->tcp.host = strdup(addr);
    }

    if (timeout) {
        if (c->timeout != timeout) {
            if (c->timeout == NULL)
                c->timeout = malloc(sizeof(struct timeval));

            memcpy(c->timeout, timeout, sizeof(struct timeval));
        }
    } else {
        if (c->timeout)
            free(c->timeout);
        c->timeout = NULL;
    }

    if (redisContextTimeoutMsec(c, &timeout_msec) != REDIS_OK) {
        __redisSetError(c, REDIS_ERR_IO, "Invalid timeout specified");
        goto error;
    }

    if (source_addr == NULL) {
        free(c->tcp.source_addr);
        c->tcp.source_addr = NULL;
    } else if (c->tcp.source_addr != source_addr) {
        free(c->tcp.source_addr);
        c->tcp.source_addr = strdup(source_addr);
    }

    snprintf(_port, 6, "%d", port);
    memset(&hints,0,sizeof(hints));
