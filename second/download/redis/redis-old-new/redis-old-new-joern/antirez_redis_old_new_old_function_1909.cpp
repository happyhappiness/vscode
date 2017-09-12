void clearNodeFailureIfNeeded(clusterNode *node) {
    int changes = 0;
    time_t now = time(NULL);

    redisAssert(node->flags & REDIS_NODE_FAIL);

    /* For slaves we always clear the FAIL flag if we can contact the
     * node again. */
    if (node->flags & REDIS_NODE_SLAVE) {
        redisLog(REDIS_NOTICE,
            "Clear FAIL state for node %.40s: slave is already reachable.",
                node->name);
        node->flags &= ~REDIS_NODE_FAIL;
        changes++;
    }

    /* If it is a master and...
     * 1) The FAIL state is old enough. We use our node timeout multiplicator
     *    plus some additional fixed time. The additional time is useful when
     *    the node timeout is extremely short and the reaction time of
     *    the cluster may be longer, so wait at least a few seconds always.
     * 2) It is yet serving slots from our point of view (not failed over).
     * Apparently no one is going to fix these slots, clear the FAIL flag. */
    if (node->flags & REDIS_NODE_MASTER &&
        node->numslots > 0 &&
        (now - node->fail_time) >
        (server.cluster_node_timeout * REDIS_CLUSTER_FAIL_UNDO_TIME_MULT +
                                        REDIS_CLUSTER_FAIL_UNDO_TIME_ADD))
    {
        redisLog(REDIS_NOTICE,
            "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                node->name);
        node->flags &= ~REDIS_NODE_FAIL;
        changes++;
    }

    /* Update state and save config. */
    if (changes) {
        clusterUpdateState();
        clusterSaveConfigOrDie();
    }
}