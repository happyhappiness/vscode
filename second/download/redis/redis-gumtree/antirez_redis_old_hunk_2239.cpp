    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master, *ri;
        sds line;

        /* sentinel monitor */
        master = dictGetVal(de);
        line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
            master->name, master->addr->ip, master->addr->port,
            master->quorum);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

