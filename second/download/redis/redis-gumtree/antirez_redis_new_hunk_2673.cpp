            server.aof_rewrite_scheduled,
            server.aof_rewrite_time_last,
            (server.aof_child_pid == -1) ?
                -1 : time(NULL)-server.aof_rewrite_time_start,
            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");

        if (server.aof_state != REDIS_AOF_OFF) {
            info = sdscatprintf(info,
