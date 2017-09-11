            return;
        }
    } else {
        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";

        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
        server.dirty++;
    }

