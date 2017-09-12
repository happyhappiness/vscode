void clusterBeforeSleep(void) {
    /* Handle failover, this is needed when it is likely that there is already
     * the quorum from masters in order to react fast. */
    if (server.cluster->todo_before_sleep & CLUSTER_TODO_HANDLE_FAILOVER)
        clusterHandleSlaveFailover();

    /* Update the cluster state. */
    if (server.cluster->todo_before_sleep & CLUSTER_TODO_UPDATE_STATE)
        clusterUpdateState();

    /* Save the config, possibly using fsync. */
    if (server.cluster->todo_before_sleep & CLUSTER_TODO_SAVE_CONFIG) {
        int fsync = server.cluster->todo_before_sleep & CLUSTER_TODO_FSYNC_CONFIG;
        clusterSaveConfigOrDie(fsync);
    }

    /* Reset our flags. */
    server.cluster->todo_before_sleep = 0;
}