        __redisAsyncDisconnect(ac);
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

        if (ac->onConnect) ac->onConnect(ac,REDIS_ERR);
        __redisAsyncDisconnect(ac);
        return REDIS_ERR;
    }

    /* Mark context as connected. */
    c->flags |= REDIS_CONNECTED;
    if (ac->onConnect) ac->onConnect(ac,REDIS_OK);
    return REDIS_OK;
}

/* This function should be called when the socket is readable.
 * It processes all replies that can be read and executes their callbacks.
 */
void redisAsyncHandleRead(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (!(c->flags & REDIS_CONNECTED)) {
        /* Abort connect was not successful. */
        if (__redisAsyncHandleConnect(ac) != REDIS_OK)
            return;
        /* Try again later when the context is still not connected. */
        if (!(c->flags & REDIS_CONNECTED))
            return;
    }

    if (redisBufferRead(c) == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        /* Always re-schedule reads */
        _EL_ADD_READ(ac);
        redisProcessCallbacks(ac);
    }
}
