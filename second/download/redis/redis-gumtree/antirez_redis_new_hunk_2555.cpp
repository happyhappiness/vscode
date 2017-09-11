        }
        if (outputlen) {
            setKey(c->db,storekey,sobj);
            notifyKeyspaceEvent("sortstore",storekey,c->db->id);
            server.dirty += outputlen;
        } else if (dbDelete(c->db,storekey)) {
            signalModifiedKey(c->db,storekey);
            notifyKeyspaceEvent("del",storekey,c->db->id);
            server.dirty++;
        }
        decrRefCount(sobj);
