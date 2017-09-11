        /* Even if the context is subscribed, pending regular callbacks will
         * get a reply before pub/sub messages arrive. */
        if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
            /* A spontaneous reply in a not-subscribed context can only be the
             * error reply that is sent when a new connection exceeds the
             * maximum number of allowed connections on the server side. This
             * is seen as an error instead of a regular reply because the
             * server closes the connection after sending it. To prevent the
             * error from being overwritten by an EOF error the connection is
             * closed here. See issue #43. */
            if ( !(c->flags & REDIS_SUBSCRIBED) && ((redisReply*)reply)->type == REDIS_REPLY_ERROR ) {
                c->err = REDIS_ERR_OTHER;
                snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
                __redisAsyncDisconnect(ac);
                return;
            }
            /* No more regular callbacks and no errors, the context *must* be subscribed. */
            assert(c->flags & REDIS_SUBSCRIBED);
            __redisGetSubscribeCallback(ac,reply,&cb);
        }

        if (cb.fn != NULL) {
