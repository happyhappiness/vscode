    }
    dictReleaseIterator(di);

    if (dstkey) {
        /* Store the resulting set into the target */
        deleteKey(c->db,dstkey);
        dictAdd(c->db->dict,dstkey,dstset);
        incrRefCount(dstkey);
    }

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
    } else {
