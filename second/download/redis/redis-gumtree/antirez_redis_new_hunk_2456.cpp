 * CLUSTER messages exchange - PING/PONG and gossip
 * -------------------------------------------------------------------------- */

/* This function checks if a given node should be marked as FAIL.
 * It happens if the following conditions are met:
 *
 * 1) We are a master node. Only master nodes can mark a node as failing.
 * 2) We received enough failure reports from other nodes via gossip.
 *    Enough means that the majority of the masters believe the node is
 *    down.
 * 3) We believe this node is in PFAIL state.
 *
 * If a failure is detected we also inform the whole cluster about this
 * event trying to force every other node to set the FAIL flag for the node.
 */
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

/* This function is called only if a node is marked as FAIL, but we are able
 * to reach it again. It checks if there are the conditions to undo the FAIL
 * state.
 *
 * Currently we only revert the FAIL state if there are no slaves for this
 * node, so that no election was possible. */
void clearNodeFailureIfNeeded(clusterNode *node) {
    if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
        node->flags &= ~REDIS_NODE_FAIL;
        clusterUpdateState();
    }
}

/* Process the gossip section of PING or PONG packets.
 * Note that this function assumes that the packet is already sanity-checked
 * by the caller, not in the content of the gossip section, but in the
