line = sdscatprintf(sdsempty(),
                "sentinel known-slave %s %s %d",
                master->name, ri->addr->ip, ri->addr->port);