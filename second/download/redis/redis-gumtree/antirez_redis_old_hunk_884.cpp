    hdr = o->ptr;
    if (updated) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
        server.dirty++;
        HLL_INVALIDATE_CACHE(hdr);
    }
