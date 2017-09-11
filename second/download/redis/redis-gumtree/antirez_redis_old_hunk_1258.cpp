        (!nodeFailed(master) && !force_ack))
    {
        if (nodeIsMaster(node)) {
            redisLog(REDIS_WARNING,
                    "Failover auth denied to %.40s: it is a master node",
                    node->name);
        } else if (master == NULL) {
            redisLog(REDIS_WARNING,
                    "Failover auth denied to %.40s: I don't know its master",
                    node->name);
        } else if (!nodeFailed(master)) {
            redisLog(REDIS_WARNING,
                    "Failover auth denied to %.40s: its master is up",
                    node->name);
        }
