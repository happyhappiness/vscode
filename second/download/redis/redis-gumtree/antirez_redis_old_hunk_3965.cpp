            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        server.dirty++;
    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
