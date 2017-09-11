    setDeferredMultiBulkLength(c, slot_replylen, num_masters);
}

void clusterCommand(client *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
