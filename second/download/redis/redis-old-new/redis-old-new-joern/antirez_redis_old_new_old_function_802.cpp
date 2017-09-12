void clusterHandleSlaveMigration(int max_slaves) {
    int j, okslaves = 0;
    clusterNode *mymaster = myself->slaveof, *target = NULL, *candidate = NULL;
    dictIterator *di;
    dictEntry *de;

    /* Step 1: Don't migrate if the cluster state is not ok. */
    if (server.cluster->state != REDIS_CLUSTER_OK) return;

    /* Step 2: Don't migrate if my master will not be left with at least
     *         'migration-barrier' slaves after my migration. */
    if (mymaster == NULL) return;
    for (j = 0; j < mymaster->numslaves; j++)
        if (!nodeFailed(mymaster->slaves[j]) &&
            !nodeTimedOut(mymaster->slaves[j])) okslaves++;
    if (okslaves <= server.cluster_migration_barrier) return;

    /* Step 3: Idenitfy a candidate for migration, and check if among the
     * masters with the greatest number of ok slaves, I'm the one with the
     * smaller node ID.
     *
     * Note that this means that eventually a replica migration will occurr
     * since slaves that are reachable again always have their FAIL flag
     * cleared. At the same time this does not mean that there are no
     * race conditions possible (two slaves migrating at the same time), but
     * this is extremely unlikely to happen, and harmless. */
    candidate = myself;
    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);
        int okslaves;

        /* Only iterate over working masters. */
        if (nodeIsSlave(node) || nodeFailed(node)) continue;
        /* If this master never had slaves so far, don't migrate. We want
         * to migrate to a master that remained orphaned, not masters that
         * were never configured to have slaves. */
        if (node->numslaves == 0) continue;
        okslaves = clusterCountNonFailingSlaves(node);

        if (okslaves == 0 && target == NULL && node->numslots > 0)
            target = node;

        if (okslaves == max_slaves) {
            for (j = 0; j < node->numslaves; j++) {
                if (memcmp(node->slaves[j]->name,
                           candidate->name,
                           REDIS_CLUSTER_NAMELEN) < 0)
                {
                    candidate = node->slaves[j];
                }
            }
        }
    }
    dictReleaseIterator(di);

    /* Step 4: perform the migration if there is a target, and if I'm the
     * candidate. */
    if (target && candidate == myself) {
        serverLog(REDIS_WARNING,"Migrating to orphaned master %.40s",
            target->name);
        clusterSetMaster(target);
    }
}