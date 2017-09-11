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

