    int retval;
    sds s = sdsnewlen(node->name, REDIS_CLUSTER_NAMELEN);

    serverLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
        node->name, newname);
    retval = dictDelete(server.cluster->nodes, s);
    sdsfree(s);
