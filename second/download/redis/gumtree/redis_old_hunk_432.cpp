     * while having still keys inside. This usually happens after a failover
     * or after a manual cluster reconfiguration operated by the admin.
     *
     * If the update message is not able to demote a master to slave (in this
     * case we'll resync with the master updating the whole key space), we
     * need to delete all the keys in the slots we lost ownership. */
    uint16_t dirty_slots[REDIS_CLUSTER_SLOTS];
    int dirty_slots_count = 0;

    /* Here we set curmaster to this node or the node this node
     * replicates to if it's a slave. In the for loop we are
     * interested to check if slots are taken away from curmaster. */
    curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;

    if (sender == myself) {
        redisLog(REDIS_WARNING,"Discarding UPDATE message about myself.");
        return;
    }

    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
        if (bitmapTestBit(slots,j)) {
            /* The slot is already bound to the sender of this message. */
            if (server.cluster->slots[j] == sender) continue;

            /* The slot is in importing state, it should be modified only
             * manually via redis-trib (example: a resharding is in progress
