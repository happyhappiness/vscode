                    (long)server.unixtime-server.repl_down_since);
            }
            info = sdscatprintf(info,
                "slave_priority:%d\r\n", server.slave_priority);
        }
        info = sdscatprintf(info,
            "connected_slaves:%lu\r\n",
