notifyKeyspaceEvent(NOTIFY_ZSET,
            (op == SET_OP_UNION) ? "zunionstore" : "zinterstore",
            dstkey,c->db->id);