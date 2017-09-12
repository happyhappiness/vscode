line = sdscatprintf(sdsempty(),"%s %s %d", option,
        server.masterhost, server.masterport);