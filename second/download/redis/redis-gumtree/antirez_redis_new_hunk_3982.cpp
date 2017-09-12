            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        touchWatchedKey(c->db,dstkey);
        server.dirty++;
    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
