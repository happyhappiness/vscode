                             server.cluster->myself->slaveof->port);
    }

    /* If we are a slave and our master is down, but is serving slots,
     * call the function that handles the failover.
     * This function is called with a small delay in order to let the
     * FAIL message to propagate after failure detection, this is not
     * strictly required but makes 99.99% of failovers mechanically
     * simpler. */
    if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
        server.cluster->myself->slaveof &&
        server.cluster->myself->slaveof->flags & REDIS_NODE_FAIL &&
        (server.unixtime - server.cluster->myself->slaveof->fail_time) >
         REDIS_CLUSTER_FAILOVER_DELAY &&
        server.cluster->myself->slaveof->numslots != 0)
    {
        clusterHandleSlaveFailover();
    }

    if (update_state) clusterUpdateState();
}

/* -----------------------------------------------------------------------------
 * Slots management
 * -------------------------------------------------------------------------- */

/* Test bit 'pos' in a generic bitmap. Return 1 if the bit is zet,
 * otherwise 0. */
int bitmapTestBit(unsigned char *bitmap, int pos) {
    off_t byte = pos/8;
