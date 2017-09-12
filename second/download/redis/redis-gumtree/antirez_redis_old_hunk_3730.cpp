         * replaced. */
        server.dirty += 1+outputlen;
        touchWatchedKey(c->db,storekey);
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
    }

    /* Cleanup */
    if (sortval->type == REDIS_LIST)
        for (j = 0; j < vectorlen; j++)
            decrRefCount(vector[j].obj);
    decrRefCount(sortval);
