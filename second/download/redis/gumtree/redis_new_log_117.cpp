notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sinterstore",
                dstkey,c->db->id);