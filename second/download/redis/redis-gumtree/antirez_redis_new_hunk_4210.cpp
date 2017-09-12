            addReplyBulk(c,ele);
        }
        dictReleaseIterator(di);
        decrRefCount(dstset);
    } else {
        /* If we have a target key where to store the resulting set
         * create this key with the result set inside */
        deleteKey(c->db,dstkey);
        if (dictSize((dict*)dstset->ptr) > 0) {
            dictAdd(c->db->dict,dstkey,dstset);
            incrRefCount(dstkey);
            addReplyLong(c,dictSize((dict*)dstset->ptr));
        } else {
            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        server.dirty++;
    }
    zfree(dv);
