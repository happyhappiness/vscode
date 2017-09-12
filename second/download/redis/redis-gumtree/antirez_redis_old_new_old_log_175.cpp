info = sdscatprintf(info,
            "master_repl_offset:%lld\r\n"
            "repl_backlog_active:%d\r\n"
            "repl_backlog_size:%lld\r\n"
            "repl_backlog_first_byte_offset:%lld\r\n"
            "repl_backlog_histlen:%lld\r\n",
            server.master_repl_offset,
            server.repl_backlog != NULL,
            server.repl_backlog_size,
            server.repl_backlog_off,;