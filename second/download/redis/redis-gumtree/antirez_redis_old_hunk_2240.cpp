        /* sentinel known-slave */
        di2 = dictGetIterator(master->slaves);
        while((de = dictNext(di)) != NULL) {
            ri = dictGetVal(de);
            line = sdscatprintf(sdsempty(),
                "sentinel known-slave %s %s %d",
                master->name, ri->addr->ip, ri->addr->port);
