    setDeferredMultiBulkLength(c, slot_replylen, num_masters);
}

void clusterCommand(redisClient *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
