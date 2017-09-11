
    /* Check if we reached the quorum. */
    if (server.cluster->failover_auth_count >= needed_quorum) {
        clusterNode *oldmaster = myself->slaveof;

        redisLog(REDIS_WARNING,
            "Failover election won: I'm the new master.");
        /* We have the quorum, perform all the steps to correctly promote
         * this slave to a master.
         *
         * 1) Turn this node into a master. */
        clusterSetNodeAsMaster(myself);
        replicationUnsetMaster();

        /* 2) Claim all the slots assigned to our master. */
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            if (clusterNodeGetSlotBit(oldmaster,j)) {
                clusterDelSlot(j);
                clusterAddSlot(myself,j);
            }
        }

        /* 3) Update my configEpoch to the epoch of the election. */
        if (myself->configEpoch < server.cluster->failover_auth_epoch) {
            myself->configEpoch = server.cluster->failover_auth_epoch;
            redisLog(REDIS_WARNING,
                "configEpoch set to %llu after successful failover",
                (unsigned long long) myself->configEpoch);
        }

        /* 4) Update state and save config. */
        clusterUpdateState();
        clusterSaveConfigOrDie(1);

        /* 5) Pong all the other nodes so that they can update the state
         *    accordingly and detect that we switched to master role. */
        clusterBroadcastPong(CLUSTER_BROADCAST_ALL);

        /* 6) If there was a manual failover in progress, clear the state. */
        resetManualFailover();
    } else {
        clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_WAITING_VOTES);
    }
