        if (!server.ds_enabled) {
            addReplyError(c, "DEBUG FLUSHCACHE called with diskstore off.");
            return;
        } else if (server.bgsavethread != (pthread_t) -1) {
            addReplyError(c, "Can't flush cache while BGSAVE is in progress.");
            return;
        } else {
            /* To flush the whole cache we need to wait for everything to
             * be flushed on disk... */
