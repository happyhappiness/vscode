        server.cluster->myself->slaveof = NULL;
        replicationUnsetMaster();

        /* 2) Ping all the other nodes so that they can update the state
         *    accordingly and detect that we switched to master role. */
        clusterBroadcastPing();
    }
}

