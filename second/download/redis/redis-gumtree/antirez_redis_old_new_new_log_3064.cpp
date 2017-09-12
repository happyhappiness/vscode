info = sdscatprintf(info,
            "connected_slaves:%d\r\n",
            listLength(server.slaves));