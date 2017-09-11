            != REDIS_OK) return;
        if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
            != REDIS_OK) return;

        if (quorum <= 0) {
            addReplyError(c, "Quorum must be 1 or greater.");
            return;
        }

        /* Make sure the IP field is actually a valid IP before passing it
         * to createSentinelRedisInstance(), otherwise we may trigger a
         * DNS lookup at runtime. */
