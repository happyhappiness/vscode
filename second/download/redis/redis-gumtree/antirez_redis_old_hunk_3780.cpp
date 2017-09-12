        val = dictGetEntryVal(de);
        /* Swap it */
        if (val->storage != REDIS_VM_MEMORY) {
            addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
        } else if (val->refcount != 1) {
            addReplySds(c,sdsnew("-ERR Object is shared\r\n"));
        } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
            dictGetEntryVal(de) = vp;
            addReply(c,shared.ok);
