            (unsigned long)sdslen(info)));
        addReplySds(c,info);
        addReply(c,shared.crlf);
    } else if (!strcasecmp(c->argv[1]->ptr,"keyslot") && c->argc == 3) {
        sds key = c->argv[2]->ptr;

        addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
    } else if (!strcasecmp(c->argv[1]->ptr,"getkeysinslot") && c->argc == 4) {
        long long maxkeys, slot;
        unsigned int numkeys, j;
        robj **keys;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)
            return;
        if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL) != REDIS_OK)
            return;
        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0 ||
            maxkeys > 1024*1024) {
            addReplyError(c,"Invalid slot or number of keys");
            return;
        }

        keys = zmalloc(sizeof(robj*)*maxkeys);
        numkeys = GetKeysInSlot(slot, keys, maxkeys);
        addReplyMultiBulkLen(c,numkeys);
        for (j = 0; j < numkeys; j++) addReplyBulk(c,keys[j]);
        zfree(keys);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
