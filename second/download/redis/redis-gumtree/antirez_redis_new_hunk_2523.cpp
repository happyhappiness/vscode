
        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
        server.dirty++;
    }

