        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Persistence\r\n"
            "loading:%d\r\n"
            "rdb_changes_since_last_save:%lld\r\n"
            "rdb_bgsave_in_progress:%d\r\n"
            "rdb_last_save_time:%ld\r\n"
            "rdb_last_bgsave_status:%s\r\n"
            "rdb_last_bgsave_time_sec:%ld\r\n"
            "rdb_current_bgsave_time_sec:%ld\r\n"
            "aof_enabled:%d\r\n"
            "aof_rewrite_in_progress:%d\r\n"
            "aof_rewrite_scheduled:%d\r\n"
            "aof_last_rewrite_time_sec:%ld\r\n"
            "aof_current_rewrite_time_sec:%ld\r\n"
            "aof_last_bgrewrite_status:%s\r\n",
            server.loading,
            server.dirty,
            server.rdb_child_pid != -1,
            server.lastsave,
            (server.lastbgsave_status == REDIS_OK) ? "ok" : "err",
            server.rdb_save_time_last,
            (server.rdb_child_pid == -1) ?
                -1 : time(NULL)-server.rdb_save_time_start,
            server.aof_state != REDIS_AOF_OFF,
            server.aof_child_pid != -1,
            server.aof_rewrite_scheduled,
            server.aof_rewrite_time_last,
            (server.aof_child_pid == -1) ?
                -1 : time(NULL)-server.aof_rewrite_time_start,
            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");

        if (server.aof_state != REDIS_AOF_OFF) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
