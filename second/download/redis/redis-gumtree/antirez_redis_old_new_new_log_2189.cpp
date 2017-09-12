notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
            incr ? "zincr" : "zadd", key, c->db->id);