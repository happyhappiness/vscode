void clearNodeFailureIfNeeded(clusterNode *node) {
    if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
        redisLog(REDIS_NOTICE,
            "Clear FAIL state for node %.40s: is reachable and has no slaves.",
                node->name);
        node->flags &= ~REDIS_NODE_FAIL;
        clusterUpdateState();
        clusterSaveConfigOrDie();
    }
}