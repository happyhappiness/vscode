            decrRefCount(value);
            addReply(c,shared.ok);
            signalModifiedKey(c->db,c->argv[1]);
            notifyKeyspaceEvent("lset",c->argv[1],c->db->id);
            server.dirty++;
        }
    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
