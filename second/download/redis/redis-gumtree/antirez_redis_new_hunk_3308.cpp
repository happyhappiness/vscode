            ci = sdscatprintf(ci,"- ");

        /* Latency from the POV of this node, link status */
        ci = sdscatprintf(ci,"%ld %ld %s",
            (long) node->ping_sent,
            (long) node->pong_received,
            node->link ? "connected" : "disconnected");

        /* Slots served by this instance */
        start = -1;
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            int bit;

            if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
                if (start == -1) start = j;
            }
            if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
                if (j == REDIS_CLUSTER_SLOTS-1) j++;

                if (start == j-1) {
                    ci = sdscatprintf(ci," %d",start);
                } else {
                    ci = sdscatprintf(ci," %d-%d",start,j-1);
                }
                start = -1;
            }
        }
    }
    ci = sdscatlen(ci,"\n",1);
    dictReleaseIterator(di);
    return ci;
}
