notifyKeyspaceEvent(
            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
            dstkey,c->db->id);