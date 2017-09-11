    dictEntry *de;
    sds line;

    /* For every master emit a "sentinel monitor" config entry. */
    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master, *ri;
        sentinelAddr *master_addr;

        /* sentinel unique ID. */
        line = sdscatprintf(sdsempty(), "sentinel myid %s", sentinel.myid);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel monitor */
        master = dictGetVal(de);
        master_addr = sentinelGetCurrentMasterAddress(master);
