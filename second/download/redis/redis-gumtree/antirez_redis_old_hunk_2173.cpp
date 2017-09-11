        /* SENTINEL MASTER <name> */
        sentinelRedisInstance *ri;

        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        addReplySentinelRedisInstance(c,ri);
