                ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                    listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
            signalModifiedKey(c->db,c->argv[1]);
            notifyKeyspaceEvent("linsert",c->argv[1],c->db->id);
            server.dirty++;
        } else {
            /* Notify client of a failed insert */
            addReply(c,shared.cnegone);
            return;
        }
    } else {
        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";

        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
        server.dirty++;
    }

