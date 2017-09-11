            server.lastsave,
            server.bgrewritechildpid != -1);

        if (server.appendonly) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
                "aof_pending_rewrite:%d\r\n",
                (long long) server.appendonly_current_size,
                (long long) server.auto_aofrewrite_base_size,
                server.aofrewrite_scheduled);
        }

        if (server.loading) {
            double perc;
            time_t eta, elapsed;
