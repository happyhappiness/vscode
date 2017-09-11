    }
    if (added) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent("sadd",c->argv[1],c->db->id);
    }
    server.dirty += added;
    addReplyLongLong(c,added);
