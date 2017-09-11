        if (setTypeSize(dstset) > 0) {
            dbAdd(c->db,dstkey,dstset);
            addReplyLongLong(c,setTypeSize(dstset));
            notifyKeyspaceEvent("sinterstore",dstkey,c->db->id);
        } else {
            decrRefCount(dstset);
            addReply(c,shared.czero);
