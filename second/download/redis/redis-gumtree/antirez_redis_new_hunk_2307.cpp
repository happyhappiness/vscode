    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (node->flags & filter) continue;

        /* Node coordinates */
        ci = sdscatprintf(ci,"%.40s %s:%d ",
            node->name,
