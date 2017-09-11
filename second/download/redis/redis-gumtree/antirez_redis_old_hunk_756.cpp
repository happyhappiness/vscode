
        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
            return;
        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS) {
            addReplyError(c,"Invalid slot");
            return;
        }
