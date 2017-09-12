static void __redisAsyncDisconnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    /* Make sure error is accessible if there is any */
    __redisAsyncCopyError(ac);

    if (ac->err == 0) {
        /* For clean disconnects, there should be no pending callbacks. */
        assert(__redisShiftCallback(&ac->replies,NULL) == REDIS_ERR);
    } else {
        /* Disconnection is caused by an error, make sure that pending
         * callbacks cannot call new commands. */
        c->flags |= REDIS_DISCONNECTING;
    }

    /* For non-clean disconnects, __redisAsyncFree() will execute pending
     * callbacks with a NULL-reply. */
    __redisAsyncFree(ac);
}