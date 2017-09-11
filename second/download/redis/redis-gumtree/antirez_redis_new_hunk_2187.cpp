 * of the CLUSTER NODES function, and as format for the cluster
 * configuration file (nodes.conf) for a given node. */
sds clusterGenNodesDescription(int filter) {
    sds ci = sdsempty(), ni;
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (node->flags & filter) continue;
        ni = clusterGenNodeDescription(node);
        ci = sdscatsds(ci,ni);
        sdsfree(ni);
        ci = sdscatlen(ci,"\n",1);
    }
    dictReleaseIterator(di);
