        myself->configEpoch = server.cluster->currentEpoch;
        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                             CLUSTER_TODO_FSYNC_CONFIG);
        redisLog(REDIS_WARNING,
            "New configEpoch set to %llu",
            (unsigned long long) myself->configEpoch);
        return REDIS_OK;
