sds clusterGenNodesDescription(void) {
    sds ci = sdsempty();
    dictIterator *di;
    dictEntry *de;

    di = dictGetIterator(server.cluster.nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetEntryVal(de);

        /* Node coordinates */
        ci = sdscatprintf(ci,"%.40s %s:%d ",
            node->name,
            node->ip,
            node->port);

        /* Flags */
        if (node->flags == 0) ci = sdscat(ci,"noflags,");
        if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
        if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
        if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
        if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
        if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
        if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
        if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';

        /* Slave of... or just "-" */
        if (node->slaveof)
            ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
        else
            ci = sdscatprintf(ci,"- ");

        /* Latency from the POV of this node, link status */
        ci = sdscatprintf(ci,"%ld %ld %s\n",
            (long) node->ping_sent,
            (long) node->pong_received,
            node->link ? "connected" : "disconnected");
    }
    dictReleaseIterator(di);
    return ci;
}