        server.cluster->currentEpoch = 0;
        server.cluster->lastVoteEpoch = 0;
        myself->configEpoch = 0;
        redisLog(REDIS_WARNING, "configEpoch set to 0 via CLUSTER RESET HARD");

        /* To change the Node ID we need to remove the old name from the
         * nodes table, change the ID, and re-add back with new name. */
