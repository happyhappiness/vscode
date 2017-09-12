info = sdscatprintf(info,
            "connected_slaves:%lu\r\n",
            listLength(server.slaves));