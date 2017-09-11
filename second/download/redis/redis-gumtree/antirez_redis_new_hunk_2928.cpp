            server.dirty,
            server.bgsavechildpid != -1,
            server.lastsave,
            server.aof_child_pid != -1);

        if (server.aof_state != REDIS_AOF_OFF) {
            info = sdscatprintf(info,
