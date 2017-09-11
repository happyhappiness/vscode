    /* For slaves we always clear the FAIL flag if we can contact the
     * node again. */
    if (nodeIsSlave(node) || node->numslots == 0) {
        redisLog(REDIS_NOTICE,
            "Clear FAIL state for node %.40s: %s is reachable again.",
                node->name,
                nodeIsSlave(node) ? "slave" : "master without slots");
