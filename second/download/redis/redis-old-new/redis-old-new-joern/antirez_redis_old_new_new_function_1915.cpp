void clusterHandleSlaveFailover(void) {
    time_t data_age = server.unixtime - server.repl_down_since;
    mstime_t auth_age = mstime() - server.cluster->failover_auth_time;
    int needed_quorum = (server.cluster->size / 2) + 1;
    int j;

    /* Pre conditions to run the function:
     * 1) We are a slave.
     * 2) Our master is flagged as FAIL.
     * 3) It is serving slots. */
    if (!(server.cluster->myself->flags & REDIS_NODE_SLAVE) ||
        server.cluster->myself->slaveof == NULL ||
        !(server.cluster->myself->slaveof->flags & REDIS_NODE_FAIL) ||
        server.cluster->myself->slaveof->numslots == 0) return;

    /* Remove the node timeout from the data age as it is fine that we are
     * disconnected from our master at least for the time it was down to be
     * flagged as FAIL, that's the baseline. */
    if (data_age > server.cluster_node_timeout)
        data_age -= server.cluster_node_timeout;

    /* Check if our data is recent enough. For now we just use a fixed
     * constant of ten times the node timeout since the cluster should
     * react much faster to a master down. */
    if (data_age >
        server.cluster_node_timeout * REDIS_CLUSTER_SLAVE_VALIDITY_MULT)
        return;

    /* Compute the time at which we can start an election. */
    if (server.cluster->failover_auth_time == 0 ||
        auth_age >
        server.cluster_node_timeout * 1000 * REDIS_CLUSTER_FAILOVER_AUTH_RETRY_MULT)
    {
        server.cluster->failover_auth_time = mstime() +
            500 + /* Fixed delay of 500 milliseconds, let FAIL msg propagate. */
            data_age * 100 + /* Add 100 milliseconds for every second of age. */
            random() % 500; /* Random delay between 0 and 500 milliseconds. */
        server.cluster->failover_auth_count = 0;
        server.cluster->failover_auth_sent = 0;
        redisLog(REDIS_WARNING,"Start of election delayed for %lld milliseconds.",
            server.cluster->failover_auth_time - mstime());
        return;
    }

    /* Return ASAP if we can't still start the election. */
    if (mstime() < server.cluster->failover_auth_time) return;

    /* Return ASAP if the election is too old to be valid. */
    if (mstime() - server.cluster->failover_auth_time > server.cluster_node_timeout * 1000)
        return;

    /* Ask for votes if needed. */
    if (server.cluster->failover_auth_sent == 0) {
        server.cluster->currentEpoch++;
        server.cluster->failover_auth_epoch = server.cluster->currentEpoch;
        redisLog(REDIS_WARNING,"Starting a failover election for epoch %llu.",
            server.cluster->currentEpoch);
        clusterRequestFailoverAuth();
        server.cluster->failover_auth_sent = 1;
        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                             CLUSTER_TODO_UPDATE_STATE|
                             CLUSTER_TODO_FSYNC_CONFIG);
        return; /* Wait for replies. */
    }

    /* Check if we reached the quorum. */
    if (server.cluster->failover_auth_count >= needed_quorum) {
        clusterNode *oldmaster = server.cluster->myself->slaveof;

        redisLog(REDIS_WARNING,
            "Failover election won: I'm the new master.");
        /* We have the quorum, perform all the steps to correctly promote
         * this slave to a master.
         *
         * 1) Turn this node into a master. */
        clusterNodeRemoveSlave(server.cluster->myself->slaveof,
                               server.cluster->myself);
        server.cluster->myself->flags &= ~REDIS_NODE_SLAVE;
        server.cluster->myself->flags |= REDIS_NODE_MASTER;
        server.cluster->myself->slaveof = NULL;
        replicationUnsetMaster();

        /* 2) Claim all the slots assigned to our master. */
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            if (clusterNodeGetSlotBit(oldmaster,j)) {
                clusterDelSlot(j);
                clusterAddSlot(server.cluster->myself,j);
            }
        }

        /* 3) Update my configEpoch to the epoch of the election. */
        server.cluster->myself->configEpoch = server.cluster->failover_auth_epoch;

        /* 4) Update state and save config. */
        clusterUpdateState();
        clusterSaveConfigOrDie(1);

        /* 5) Pong all the other nodes so that they can update the state
         *    accordingly and detect that we switched to master role. */
        clusterBroadcastPong();
    }
}