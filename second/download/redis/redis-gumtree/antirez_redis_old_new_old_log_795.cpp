serverLog(REDIS_WARNING, "Failover auth granted to %.40s for epoch %llu",
        node->name, (unsigned long long) server.cluster->currentEpoch);