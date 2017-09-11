            "last_save_time:%ld\r\n"
            "bgrewriteaof_in_progress:%d\r\n",
            server.loading,
            server.appendonly,
            server.dirty,
            server.bgsavechildpid != -1,
            server.lastsave,
            server.bgrewritechildpid != -1);

        if (server.appendonly) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
