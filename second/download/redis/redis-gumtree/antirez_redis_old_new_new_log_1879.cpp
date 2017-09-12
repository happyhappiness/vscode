line = sdscatprintf(sdsempty(),
                "sentinel known-sentinel %s %s %d",
                master->name, ri->addr->ip, ri->addr->port);