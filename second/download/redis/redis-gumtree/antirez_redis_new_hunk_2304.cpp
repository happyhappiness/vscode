    node->flags |= REDIS_NODE_FAIL;
    node->fail_time = time(NULL);

    /* Broadcast the failing node name to everybody, forcing all the other
     * reachable nodes to flag the node as FAIL. */
    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
        clusterSendFail(node->name);
    clusterUpdateState();
    clusterSaveConfigOrDie();
}
