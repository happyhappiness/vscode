        (now - node->fail_time) >
        (server.cluster_node_timeout * REDIS_CLUSTER_FAIL_UNDO_TIME_MULT))
    {
        serverLog(LL_NOTICE,
            "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                node->name);
        node->flags &= ~REDIS_NODE_FAIL;
