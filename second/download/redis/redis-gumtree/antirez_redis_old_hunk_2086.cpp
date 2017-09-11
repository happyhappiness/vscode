        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
        server.dirty++;
    }
    addReply(c, updated ? shared.cone : shared.czero);
}
