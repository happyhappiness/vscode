void markNodeAsFailingIfNeeded(clusterNode *node) {
    int failures;
    int needed_quorum = (server.cluster->size / 2) + 1;

    if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return;
    if (!(node->flags & REDIS_NODE_PFAIL)) return; /* We can reach it. */
    if (node->flags & REDIS_NODE_FAIL) return; /* Already FAILing. */

    failures = 1 + clusterNodeFailureReportsCount(node); /* +1 is for myself. */
    if (failures < needed_quorum) return;

    redisLog(REDIS_NOTICE,
        "Marking node %.40s as failing (quorum reached).", node->name);

    /* Mark the node as failing. */
    node->flags &= ~REDIS_NODE_PFAIL;
    node->flags |= REDIS_NODE_FAIL;

    /* Broadcast the failing node name to everybody */
    clusterSendFail(node->name);
    clusterUpdateState();
    clusterSaveConfigOrDie();
}