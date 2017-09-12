         * replaced. */
        server.dirty += 1+outputlen;
        touchWatchedKey(c->db,storekey);
        addReplyLongLong(c,outputlen);
    }

    /* Cleanup */
