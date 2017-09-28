line = sdscatprintf(sdsempty(),
                "sentinel known-sentinel %s %s %d %s",
                master->name, ri->addr->ip, ri->addr->port, ri->runid);