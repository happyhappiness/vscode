            addReplyError(c, "DEBUG FLUSHCACHE called with diskstore off.");
            return;
        } else {
            /* To flush the whole cache we need to wait for everything to
             * be flushed on disk... */
            cacheForcePointInTime();
            emptyDb();
            addReply(c,shared.ok);
            return;
