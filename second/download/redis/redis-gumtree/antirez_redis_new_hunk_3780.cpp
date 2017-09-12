        val = dictGetEntryVal(de);
        /* Swap it */
        if (val->storage != REDIS_VM_MEMORY) {
            addReplyError(c,"This key is not in memory");
        } else if (val->refcount != 1) {
            addReplyError(c,"Object is shared");
        } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
            dictGetEntryVal(de) = vp;
            addReply(c,shared.ok);
