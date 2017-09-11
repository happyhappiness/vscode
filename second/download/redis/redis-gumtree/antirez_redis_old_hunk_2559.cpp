    decrRefCount(new);
    addReplyLongLong(c,value);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
}

