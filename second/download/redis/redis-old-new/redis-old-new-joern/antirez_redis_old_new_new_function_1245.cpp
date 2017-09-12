void clusterFailoverReplaceYourMaster(void) {
    int j;
    clusterNode *oldmaster = myself->slaveof;

    if (nodeIsMaster(myself) || oldmaster == NULL) return;

    /* 1) Turn this node into a master. */
    clusterSetNodeAsMaster(myself);
    replicationUnsetMaster();

    /* 2) Claim all the slots assigned to our master. */
    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
        if (clusterNodeGetSlotBit(oldmaster,j)) {
            clusterDelSlot(j);
            clusterAddSlot(myself,j);
        }
    }

    /* 3) Update state and save config. */
    clusterUpdateState();
    clusterSaveConfigOrDie(1);

    /* 4) Pong all the other nodes so that they can update the state
     *    accordingly and detect that we switched to master role. */
    clusterBroadcastPong(CLUSTER_BROADCAST_ALL);

    /* 5) If there was a manual failover in progress, clear the state. */
    resetManualFailover();
}