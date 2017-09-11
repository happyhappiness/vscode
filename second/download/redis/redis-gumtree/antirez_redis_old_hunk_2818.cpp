        /* Even if the context is subscribed, pending regular callbacks will
         * get a reply before pub/sub messages arrive. */
        if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
            /* No more regular callbacks, the context *must* be subscribed. */
            assert(c->flags & REDIS_SUBSCRIBED);
            __redisGetSubscribeCallback(ac,reply,&cb);
        }

        if (cb.fn != NULL) {
            __redisRunCallback(ac,&cb,reply);
            c->fn->freeObject(reply);

            /* Proceed with free'ing when redisAsyncFree() was called. */
            if (c->flags & REDIS_FREEING) {
