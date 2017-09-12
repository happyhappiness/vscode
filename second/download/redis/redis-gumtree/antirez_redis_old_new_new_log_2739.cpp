info = sdscatprintf(info,
                    "master_link_down_since_seconds:%ld\r\n",
                    (long)time(NULL)-server.repl_down_since);