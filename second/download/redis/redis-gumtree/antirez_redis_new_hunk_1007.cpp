                "slave_repl_offset:%lld\r\n"
                ,server.masterhost,
                server.masterport,
                (server.repl_state == REPL_STATE_CONNECTED) ?
                    "up" : "down",
                server.master ?
                ((int)(server.unixtime-server.master->lastinteraction)) : -1,
                server.repl_state == REPL_STATE_TRANSFER,
                slave_repl_offset
            );

            if (server.repl_state == REPL_STATE_TRANSFER) {
                info = sdscatprintf(info,
                    "master_sync_left_bytes:%lld\r\n"
                    "master_sync_last_io_seconds_ago:%d\r\n"
