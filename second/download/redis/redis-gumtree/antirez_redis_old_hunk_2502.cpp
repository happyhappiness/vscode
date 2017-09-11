        } else {
            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        signalModifiedKey(c->db,dstkey);
        server.dirty++;
