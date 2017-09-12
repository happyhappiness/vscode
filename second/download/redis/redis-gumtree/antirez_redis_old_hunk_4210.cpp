            addReplyBulk(c,ele);
        }
        dictReleaseIterator(di);
    } else {
        /* If we have a target key where to store the resulting set
         * create this key with the result set inside */
        deleteKey(c->db,dstkey);
        if (dictSize((dict*)dstset->ptr) > 0) {
            dictAdd(c->db->dict,dstkey,dstset);
            incrRefCount(dstkey);
        } else {
            decrRefCount(dstset);
        }
    }

    /* Cleanup */
    if (!dstkey) {
        decrRefCount(dstset);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
            dictSize((dict*)dstset->ptr)));
        server.dirty++;
    }
    zfree(dv);
