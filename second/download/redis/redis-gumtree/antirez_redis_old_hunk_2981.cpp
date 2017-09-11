
    di = dictGetIterator(server.cluster.nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetEntryVal(de);

        /* Node coordinates */
        ci = sdscatprintf(ci,"%.40s %s:%d ",
