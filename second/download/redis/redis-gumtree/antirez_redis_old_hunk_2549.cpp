
    if (deleted) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent("zrembyrank",key,c->db->id);
        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
    }
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
