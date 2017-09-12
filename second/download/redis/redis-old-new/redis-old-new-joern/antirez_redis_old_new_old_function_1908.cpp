void markNodeAsFailingIfNeeded(clusterNode *node) {
    int failures;
    int needed_quorum = (server.cluster->size / 2) + 1;

    if (!(node->flags & REDIS_NODE_PFAIL)) return; /* We can reach it. */
    if (node->flags & REDIS_NODE_FAIL) return; /* Already FAILing. */

    failures = clusterNodeFailureReportsCount(node);
    /* Also count myself as a voter if I'm a master. */
    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
        failures += 1;
    if (failures < needed_quorum) return; /* No weak agreement from masters. */

    redisLog(REDIS_NOTICE,
        "Marking node %.40s as failing (quorum reached).", node->name);

    /* Mark the node as failing. */
    node->flags &= ~REDIS_NODE_PFAIL;
    node->flags |= REDIS_NODE_FAIL;
    node->fail_time = time(NULL);

    /* Broadcast the failing node name to everybody, forcing all the other
     * reachable nodes to flag the node as FAIL. */
    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
        clusterSendFail(node->name);
    clusterUpdateState();
    clusterSaveConfigOrDie();
}