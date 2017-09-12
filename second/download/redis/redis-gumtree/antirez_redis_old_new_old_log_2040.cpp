line = sdscatprintf(sdsempty(),"slaveof %s %d",
        server.masterhost, server.masterport);