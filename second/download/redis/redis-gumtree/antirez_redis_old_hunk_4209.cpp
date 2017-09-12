        if (dictSize((dict*)dstset->ptr) > 0) {
            dictAdd(c->db->dict,dstkey,dstset);
            incrRefCount(dstkey);
        } else {
            decrRefCount(dstset);
        }
    }

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
            dictSize((dict*)dstset->ptr)));
        server.dirty++;
    }
    zfree(dv);
}
