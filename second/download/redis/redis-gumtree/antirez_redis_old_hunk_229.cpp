            (intmax_t)server.rdb_save_time_last,
            (intmax_t)((server.rdb_child_pid == -1) ?
                -1 : time(NULL)-server.rdb_save_time_start),
            server.aof_state != AOF_OFF,
            server.aof_child_pid != -1,
            server.aof_rewrite_scheduled,
            (intmax_t)server.aof_rewrite_time_last,
            (intmax_t)((server.aof_child_pid == -1) ?
                -1 : time(NULL)-server.aof_rewrite_time_start),
            (server.aof_lastbgrewrite_status == C_OK) ? "ok" : "err",
            (server.aof_last_write_status == C_OK) ? "ok" : "err");

        if (server.aof_state != AOF_OFF) {
            info = sdscatprintf(info,
