            }
        }
        info = sdscatprintf(info,
            "connected_slaves:%lu\r\n",
            listLength(server.slaves));
        if (listLength(server.slaves)) {
            int slaveid = 0;
