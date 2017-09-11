        __redisAsyncDisconnect(ac);
}

/* This function should be called when the socket is readable.
 * It processes all replies that can be read and executes their callbacks.
 */
void redisAsyncHandleRead(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (redisBufferRead(c) == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        /* Always re-schedule reads */
        if (ac->ev.addRead) ac->ev.addRead(ac->ev.data);
        redisProcessCallbacks(ac);
    }
}
