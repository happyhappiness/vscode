         * replaced. */
        server.dirty += 1+outputlen;
        touchWatchedKey(c->db,storekey);
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
    }

    /* Cleanup */
