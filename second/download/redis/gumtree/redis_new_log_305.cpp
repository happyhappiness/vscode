line = sdscatprintf(sdsempty(),
                "sentinel known-slave %s %s %d",
                master->name, slave_addr->ip, slave_addr->port);