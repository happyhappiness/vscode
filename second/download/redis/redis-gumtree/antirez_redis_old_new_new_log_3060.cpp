info = sdscatprintf(info,
            "# Persistence\r\n"
            "loading:%d\r\n"
            "aof_enabled:%d\r\n"
            "changes_since_last_save:%lld\r\n"
            "bgsave_in_progress:%d\r\n"
            "last_save_time:%ld\r\n"
            "bgrewriteaof_in_progress:%d\r\n",
            server.loading,
            server.appendonly,
            server.dirty,
                server.bgsavechildpid != -1 ||
                server.bgsavethread != (pthread_t) -1,
            server.lastsave,
            server.bgrewritechildpid != -1);