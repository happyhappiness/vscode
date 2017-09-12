        if (dictSize((dict*)dstset->ptr) > 0) {
            dictAdd(c->db->dict,dstkey,dstset);
            incrRefCount(dstkey);
            addReplyLong(c,dictSize((dict*)dstset->ptr));
        } else {
            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        server.dirty++;
    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    }
    zfree(dv);
}
