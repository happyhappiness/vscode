        totlen = sdslen(o->ptr);
    }
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent("append",c->argv[1],c->db->id);
    server.dirty++;
    addReplyLongLong(c,totlen);
}
