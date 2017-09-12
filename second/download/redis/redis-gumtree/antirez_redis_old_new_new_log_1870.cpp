line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
            master->name, master->addr->ip, master->addr->port,
            master->quorum);