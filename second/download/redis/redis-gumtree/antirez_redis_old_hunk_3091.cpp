                    (int)(time(NULL)-server.repl_transfer_lastio)
                );
            }
        }
        info = sdscatprintf(info,
            "connected_slaves:%d\r\n",
