    node->flags |= REDIS_NODE_FAIL;
    node->fail_time = time(NULL);

    /* Broadcast the failing node name to everybody */
    clusterSendFail(node->name);
    clusterUpdateState();
    clusterSaveConfigOrDie();
}
