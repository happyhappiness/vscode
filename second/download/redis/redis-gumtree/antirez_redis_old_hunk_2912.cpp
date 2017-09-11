                "master_sync_in_progress:%d\r\n"
                ,server.masterhost,
                server.masterport,
                (server.replstate == REDIS_REPL_CONNECTED) ?
                    "up" : "down",
                server.master ?
                ((int)(time(NULL)-server.master->lastinteraction)) : -1,
                server.replstate == REDIS_REPL_TRANSFER
            );

            if (server.replstate == REDIS_REPL_TRANSFER) {
                info = sdscatprintf(info,
                    "master_sync_left_bytes:%ld\r\n"
                    "master_sync_last_io_seconds_ago:%d\r\n"
