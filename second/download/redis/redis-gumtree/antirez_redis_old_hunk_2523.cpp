
        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
        server.dirty++;
    }

