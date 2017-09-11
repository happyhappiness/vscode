        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);

        /* Replicate/AOF this command as an SREM operation */
        aux = createStringObject("DEL",3);
        rewriteClientCommandVector(c,2,aux,c->argv[1]);
        decrRefCount(aux);

        return;
    }

