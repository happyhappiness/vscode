
            /* dictAdd will not add the same element multiple times */
            ele = dictGetEntryKey(de);
            if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
                incrRefCount(ele);
                if (!dstkey) {
                    addReplySds(c,sdscatprintf(sdsempty(),
                            "$%d\r\n",sdslen(ele->ptr)));
                    addReply(c,ele);
                    addReply(c,shared.crlf);
                    cardinality++;
                }
            }
        }
        dictReleaseIterator(di);
    }

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
        decrRefCount(dstset);
    } else {
        addReply(c,shared.ok);
