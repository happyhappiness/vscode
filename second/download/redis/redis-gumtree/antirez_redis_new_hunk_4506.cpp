    if (!dstkey) {
        decrRefCount(dstset);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
            dictSize((dict*)dstset->ptr)));
        server.dirty++;
    }
    zfree(dv);
