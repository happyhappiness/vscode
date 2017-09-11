        (long long) node->ping_sent,
        (long long) node->pong_received,
        (unsigned long long) node->configEpoch,
        (node->link || node->flags & CLUSTER_NODE_MYSELF) ?
                    "connected" : "disconnected");

    /* Slots served by this instance */
    start = -1;
    for (j = 0; j < CLUSTER_SLOTS; j++) {
        int bit;

        if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
            if (start == -1) start = j;
        }
        if (start != -1 && (!bit || j == CLUSTER_SLOTS-1)) {
            if (bit && j == CLUSTER_SLOTS-1) j++;

            if (start == j-1) {
                ci = sdscatprintf(ci," %d",start);
