
    if (dbDelete(c->db,dstkey)) {
        signalModifiedKey(c->db,dstkey);
        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
        touched = 1;
        server.dirty++;
    }
