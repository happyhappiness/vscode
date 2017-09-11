
        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
            == NULL) return;
        sentinelEvent(LL_WARNING,"-monitor",ri,"%@");
        dictDelete(sentinel.masters,c->argv[2]->ptr);
        sentinelFlushConfig();
        addReply(c,shared.ok);
