            }
        }
        info = sdscatprintf(info,
            "connected_slaves:%d\r\n",
            listLength(server.slaves));
        if (listLength(server.slaves)) {
            int slaveid = 0;
