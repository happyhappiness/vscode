        di2 = dictGetIterator(master->sentinels);
        while((de = dictNext(di2)) != NULL) {
            ri = dictGetVal(de);
            line = sdscatprintf(sdsempty(),
                "sentinel known-sentinel %s %s %d%s%s",
                master->name, ri->addr->ip, ri->addr->port,
                ri->runid ? " " : "",
                ri->runid ? ri->runid : "");
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);
