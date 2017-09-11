        myself->configEpoch = server.cluster->currentEpoch;
        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                             CLUSTER_TODO_FSYNC_CONFIG);
        serverLog(LL_WARNING,
            "New configEpoch set to %llu",
            (unsigned long long) myself->configEpoch);
        return C_OK;
