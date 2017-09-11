            (server.aof_lastbgrewrite_status == C_OK) ? "ok" : "err",
            (server.aof_last_write_status == C_OK) ? "ok" : "err");

        if (server.aof_state != AOF_OFF) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
