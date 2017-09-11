    c->errstr[0] = '\0';
    c->obuf = sdsempty();
    c->reader = redisReaderCreate();
    c->tcp.host = NULL;
    c->tcp.source_addr = NULL;
    c->unix_sock.path = NULL;
    c->timeout = NULL;

    if (c->obuf == NULL || c->reader == NULL) {
        redisFree(c);
        return NULL;
    }

    return c;
}

void redisFree(redisContext *c) {
    if (c == NULL)
        return;
    if (c->fd > 0)
        close(c->fd);
    if (c->obuf != NULL)
        sdsfree(c->obuf);
    if (c->reader != NULL)
        redisReaderFree(c->reader);
    if (c->tcp.host)
        free(c->tcp.host);
    if (c->tcp.source_addr)
        free(c->tcp.source_addr);
    if (c->unix_sock.path)
        free(c->unix_sock.path);
    if (c->timeout)
        free(c->timeout);
    free(c);
}

int redisFreeKeepFd(redisContext *c) {
    int fd = c->fd;
    c->fd = -1;
    redisFree(c);
    return fd;
}

int redisReconnect(redisContext *c) {
    c->err = 0;
    memset(c->errstr, '\0', strlen(c->errstr));

    if (c->fd > 0) {
        close(c->fd);
    }

    sdsfree(c->obuf);
    redisReaderFree(c->reader);

    c->obuf = sdsempty();
    c->reader = redisReaderCreate();

    if (c->connection_type == REDIS_CONN_TCP) {
        return redisContextConnectBindTcp(c, c->tcp.host, c->tcp.port,
                c->timeout, c->tcp.source_addr);
    } else if (c->connection_type == REDIS_CONN_UNIX) {
        return redisContextConnectUnix(c, c->unix_sock.path, c->timeout);
    } else {
        /* Something bad happened here and shouldn't have. There isn't
           enough information in the context to reconnect. */
        __redisSetError(c,REDIS_ERR_OTHER,"Not enough information to reconnect");
    }

    return REDIS_ERR;
}

/* Connect to a Redis instance. On error the field error in the returned
