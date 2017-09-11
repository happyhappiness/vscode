                slave_addr = master->addr;
            line = sdscatprintf(sdsempty(),
                "sentinel known-slave %s %s %d",
                master->name, slave_addr->ip, slave_addr->port);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);
