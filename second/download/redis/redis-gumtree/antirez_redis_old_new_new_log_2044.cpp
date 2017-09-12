line = sdscatprintf(sdsempty(),"save %ld %d",
            server.saveparams[j].seconds, server.saveparams[j].changes);