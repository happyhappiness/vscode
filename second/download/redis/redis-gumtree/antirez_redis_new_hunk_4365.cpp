    }

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
            dictSize((dict*)dstset->ptr)));
        server.dirty++;
    }
