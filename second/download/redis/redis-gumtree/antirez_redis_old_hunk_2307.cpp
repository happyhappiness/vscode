    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        /* Node coordinates */
        ci = sdscatprintf(ci,"%.40s %s:%d ",
            node->name,
