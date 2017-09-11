        di2 = dictGetIterator(master->sentinels);
        while((de = dictNext(di2)) != NULL) {
            ri = dictGetVal(de);
            if (ri->runid == NULL) continue;
            line = sdscatprintf(sdsempty(),
                "sentinel known-sentinel %s %s %d %s",
                master->name, ri->addr->ip, ri->addr->port, ri->runid);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);
