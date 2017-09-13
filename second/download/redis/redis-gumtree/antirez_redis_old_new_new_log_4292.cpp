addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
            dictSize((dict*)dstset->ptr)));