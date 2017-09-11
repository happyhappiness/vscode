        /* Feed slaves that are waiting for the initial SYNC (so these commands
         * are queued in the output buffer until the initial SYNC completes),
         * or are already in sync with the master. */

        /* First, trasmit the object created from the static buffer. */
        addReply(slave,o);

        /* Finally any additional argument that was not stored inside the
         * static buffer if any (from j to argc). */
        for (i = j; i < argc; i++)
            addReplyBulk(slave,argv[i]);
    }
    decrRefCount(o);
}

void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
