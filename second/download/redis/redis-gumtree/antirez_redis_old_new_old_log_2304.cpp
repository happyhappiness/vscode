info = sdscatprintf(info,
                    "master_sync_left_bytes:%ld\r\n"
                    "master_sync_last_io_seconds_ago:%d\r\n"
                    ,(long)server.repl_transfer_left,
                    (int)(server.unixtime-server.repl_transfer_lastio)
                );