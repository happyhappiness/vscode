            master->name, (unsigned long long) master->config_epoch);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel leader-epoch */
        line = sdscatprintf(sdsempty(),
            "sentinel leader-epoch %s %llu",
            master->name, (unsigned long long) master->leader_epoch);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel known-slave */
        di2 = dictGetIterator(master->slaves);
        while((de = dictNext(di2)) != NULL) {
