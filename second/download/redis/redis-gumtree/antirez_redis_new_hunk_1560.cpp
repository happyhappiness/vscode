        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);

        /* Replicate/AOF this command as an SREM operation */
        rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
        return;
    }

