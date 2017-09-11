        redisPanic("Unknown sorted set encoding");
    }

    if (deleted) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyscore",key,c->db->id);
        if (keyremoved)
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
    }
