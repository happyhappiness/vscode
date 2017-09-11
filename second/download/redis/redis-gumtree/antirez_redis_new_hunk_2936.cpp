            "last_save_time:%ld\r\n"
            "bgrewriteaof_in_progress:%d\r\n",
            server.loading,
            server.aof_state != REDIS_AOF_OFF,
            server.dirty,
            server.bgsavechildpid != -1,
            server.lastsave,
            server.bgrewritechildpid != -1);

        if (server.aof_state != REDIS_AOF_OFF) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
