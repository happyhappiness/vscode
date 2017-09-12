info = sdscatprintf(info,
                    "master_link_down_since_seconds:%ld\r\n",
                    (long)server.unixtime-server.repl_down_since);