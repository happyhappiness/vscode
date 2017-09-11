        }
        if (outputlen) {
            setKey(c->db,storekey,sobj);
            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"sortstore",storekey,
                                c->db->id);
            server.dirty += outputlen;
        } else if (dbDelete(c->db,storekey)) {
            signalModifiedKey(c->db,storekey);
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",storekey,c->db->id);
            server.dirty++;
        }
        decrRefCount(sobj);
