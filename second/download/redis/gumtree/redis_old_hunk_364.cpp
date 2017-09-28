    }
    replicationDiscardCachedMaster();
    cancelReplicationHandshake();
    server.repl_state = REDIS_REPL_NONE;
}

void slaveofCommand(redisClient *c) {
    /* SLAVEOF is not allowed in cluster mode as replication is automatically
     * configured using the current address of the master node. */
    if (server.cluster_enabled) {
        addReplyError(c,"SLAVEOF not allowed in cluster mode.");
        return;
