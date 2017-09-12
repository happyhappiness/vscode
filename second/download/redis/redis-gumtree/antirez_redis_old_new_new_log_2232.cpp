notifyKeyspaceEvent(
                op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
                dstkey,c->db->id);