}

/* Internal helper function to detect socket status the first time a read or
 * write event fires. When connecting was not succesful, the connect callback
 * is called with a REDIS_ERR status and the context is free'd. */
static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (redisCheckSocketError(c,c->fd) == REDIS_ERR) {
        /* Try again later when connect(2) is still in progress. */
        if (errno == EINPROGRESS)
            return REDIS_OK;
