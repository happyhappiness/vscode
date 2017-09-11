        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
        server.dirty++;
        /* Invalidate the cached cardinality. */
        registers[REDIS_HLL_SIZE-1] |= (1<<7);
    }
    addReply(c, updated ? shared.cone : shared.czero);
}
