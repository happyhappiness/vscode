        unsigned int numkeys, j;
        robj **keys;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
            return;
        if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL)
            != C_OK)
            return;
        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0) {
            addReplyError(c,"Invalid slot or number of keys");
