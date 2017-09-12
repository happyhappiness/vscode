
            /* dictAdd will not add the same element multiple times */
            ele = dictGetEntryKey(de);
            if (op == REDIS_OP_UNION || j == 0) {
                if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
                    incrRefCount(ele);
                    cardinality++;
                }
            } else if (op == REDIS_OP_DIFF) {
                if (dictDelete(dstset->ptr,ele) == DICT_OK) {
                    cardinality--;
                }
            }
        }
        dictReleaseIterator(di);
    }

    /* Output the content of the resulting set, if not in STORE mode */
    if (!dstkey) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
        di = dictGetIterator(dstset->ptr);
        if (!di) oom("dictGetIterator");
        while((de = dictNext(di)) != NULL) {
            robj *ele;

            ele = dictGetEntryKey(de);
            addReplySds(c,sdscatprintf(sdsempty(),
                    "$%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
        }
        dictReleaseIterator(di);
    }

    /* Cleanup */
    if (!dstkey) {
        decrRefCount(dstset);
    } else {
        addReply(c,shared.ok);
