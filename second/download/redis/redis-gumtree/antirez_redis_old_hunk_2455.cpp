 * node, so that no election was possible. */
void clearNodeFailureIfNeeded(clusterNode *node) {
    if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
        node->flags &= ~REDIS_NODE_FAIL;
        clusterUpdateState();
        redisLog(REDIS_NOTICE,
            "Clear FAIL state for node %.40s: is reachable and has no slaves.",
                node->name);
    }
}

