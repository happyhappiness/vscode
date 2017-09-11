    if (server.cluster_enabled) clusterPropagatePublish(c->argv[1],c->argv[2]);
    addReplyLongLong(c,receivers);
}
