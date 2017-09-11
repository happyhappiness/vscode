    }
    if (updated) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
        server.dirty++;
        /* Invalidate the cached cardinality. */
        registers[REDIS_HLL_SIZE-1] |= (1<<7);
