     * reachable nodes to flag the node as FAIL. */
    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
        clusterSendFail(node->name);
    clusterUpdateState();
    clusterSaveConfigOrDie();
}

/* This function is called only if a node is marked as FAIL, but we are able
 * to reach it again. It checks if there are the conditions to undo the FAIL
 * state. */
void clearNodeFailureIfNeeded(clusterNode *node) {
    int changes = 0;
    time_t now = time(NULL);

    redisAssert(node->flags & REDIS_NODE_FAIL);
