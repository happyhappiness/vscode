addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
            dictSize((dict*)dstset->ptr)));