sds clusterGenNodeDescription(sds ci, clusterNode *node) {
    int j, start;

    /* Node coordinates */
    ci = sdscatlen(ci,node->name,40);
    ci = sdscatfmt(ci," %s:%i ",node->ip,node->port);

    /* Flags */
    ci = representRedisNodeFlags(ci, node->flags);

    /* Slave of... or just "-" */
    if (node->slaveof) {
        ci = sdscatlen(ci," ",1);
        ci = sdscatlen(ci,node->slaveof->name,40);
        ci = sdscatlen(ci," ",1);
    } else {
        ci = sdscatlen(ci," - ",3);
    }

    /* Latency from the POV of this node, link status */
    ci = sdscatfmt(ci,"%I %I %U %s",
        (long long) node->ping_sent,
        (long long) node->pong_received,
        (unsigned long long) node->configEpoch,
        (node->link || node->flags & REDIS_NODE_MYSELF) ?
                    "connected" : "disconnected");

    /* Slots served by this instance */
    start = -1;
    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
        int bit;

        /* It is common for a node to have pretty contiguous slots, so
         * optimize this loop by skipping whole 32bit words if they have
         * no set bits. We stop to the penultimate word because last word
         * has special handling when start != -1 (later in the loop). */
        if ((j&31)==0 && j < REDIS_CLUSTER_SLOTS-32) {
            uint32_t *slotword = ((uint32_t*)node->slots)+(j/32);
            if ((start == -1 && *slotword == 0) ||
                (start != -1 && *slotword == UINT32_MAX)) {
                j += 32;
                continue;
            }
        }

        if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
            if (start == -1) start = j;
        }
        if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
            if (bit && j == REDIS_CLUSTER_SLOTS-1) j++;

            if (start == j-1) {
                ci = sdscatprintf(ci," %d",start);
            } else {
                ci = sdscatprintf(ci," %d-%d",start,j-1);
            }
            start = -1;
        }
    }

    /* Just for MYSELF node we also dump info about slots that
     * we are migrating to other instances or importing from other
     * instances. */
    if (node->flags & REDIS_NODE_MYSELF) {
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            if (server.cluster->migrating_slots_to[j]) {
                ci = sdscatprintf(ci," [%d->-%.40s]",j,
                    server.cluster->migrating_slots_to[j]->name);
            } else if (server.cluster->importing_slots_from[j]) {
                ci = sdscatprintf(ci," [%d-<-%.40s]",j,
                    server.cluster->importing_slots_from[j]->name);
            }
        }
    }
    return ci;
}