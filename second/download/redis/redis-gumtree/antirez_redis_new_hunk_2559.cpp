    decrRefCount(new);
    addReplyLongLong(c,value);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent("hincrby",c->argv[1],c->db->id);
    server.dirty++;
}

