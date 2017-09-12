    }

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
            dictSize((dict*)dstset->ptr)));
        server.dirty++;
    }
