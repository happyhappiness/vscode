void clusterHandleSlaveFailover(void) {
    time_t data_age = server.unixtime - server.repl_down_since;
    time_t auth_age = server.unixtime - server.cluster->failover_auth_time;
    int needed_quorum = (server.cluster->size / 2) + 1;
    int j;

    /* Check if our data is recent enough. For now we just use a fixed
     * constant of ten times the node timeout since the cluster should
     * react much faster to a master down. */
    if (data_age > server.cluster->node_timeout * 10) return;

    /* TODO: check if we are the first slave as well? Or just rely on the
     * master authorization? */

    /* Ask masters if we are authorized to perform the failover. If there
     * is a pending auth request that's too old, reset it. */
    if (server.cluster->failover_auth_time == 0 || auth_age > 15)
    {
        redisLog(REDIS_WARNING,"Asking masters if I can failover...");
        server.cluster->failover_auth_time = time(NULL);
        server.cluster->failover_auth_count = 0;
        clusterRequestFailoverAuth();
        return; /* Wait for replies. */
    }

    /* Check if we reached the quorum. */
    if (server.cluster->failover_auth_count >= needed_quorum) {
        clusterNode *oldmaster = server.cluster->myself->slaveof;

        redisLog(REDIS_WARNING,
            "Masters quorum reached: failing over my (failing) master.");
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

        /* 3) Ping all the other nodes so that they can update the state
         *    accordingly and detect that we switched to master role. */
        clusterBroadcastPing();

        /* 4) Update state and save config. */
        clusterUpdateState();
        clusterSaveConfigOrDie();
    }
}