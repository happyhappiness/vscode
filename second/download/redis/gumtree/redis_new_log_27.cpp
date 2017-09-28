line = sdscatprintf(sdsempty(),"%s %s", option,
        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");