    return REDIS_ERR;
}

/* Tries to do a clean disconnect from Redis, meaning it stops new commands
 * from being issued, but tries to flush the output buffer and execute
 * callbacks for all remaining replies.
 *
 * This functions is generally called from within a callback, so the
 * processCallbacks function will pick up the flag when there are no
 * more replies. */
void redisAsyncDisconnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    c->flags |= REDIS_DISCONNECTING;
}

/* Helper function to make the disconnect happen and clean up. */
static void __redisAsyncDisconnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisCallback cb;
    int status;

    /* Make sure error is accessible if there is any */
    __redisAsyncCopyError(ac);
    status = (ac->err == 0) ? REDIS_OK : REDIS_ERR;

    if (status == REDIS_OK) {
        /* When the connection is cleanly disconnected, there should not
         * be pending callbacks. */
        assert(__redisShiftCallback(&ac->replies,NULL) == REDIS_ERR);
    } else {
        /* Callbacks should not be able to issue new commands. */
        c->flags |= REDIS_DISCONNECTING;

        /* Execute pending callbacks with NULL reply. */
        while (__redisShiftCallback(&ac->replies,&cb) == REDIS_OK) {
            if (cb.fn != NULL)
                cb.fn(ac,NULL,cb.privdata);
        }
    }

    /* Signal event lib to clean up */
    if (ac->evCleanup) ac->evCleanup(ac->_adapter_data);

    /* Execute callback with proper status */
    if (ac->onDisconnect) ac->onDisconnect(ac,status);

    /* Cleanup self */
    redisFree(c);
}

void redisProcessCallbacks(redisAsyncContext *ac) {
