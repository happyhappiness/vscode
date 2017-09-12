         * replaced. */
        server.dirty += 1+outputlen;
        touchWatchedKey(c->db,storekey);
        addReplyLongLong(c,outputlen);
    }

    /* Cleanup */
    if (sortval->type == REDIS_LIST || sortval->type == REDIS_SET)
        for (j = 0; j < vectorlen; j++)
            decrRefCount(vector[j].obj);
    decrRefCount(sortval);
