                server.slave_priority,
                server.repl_slave_ro);
        }
        info = sdscatprintf(info,
            "connected_slaves:%lu\r\n",
            listLength(server.slaves));
        if (listLength(server.slaves)) {
            int slaveid = 0;
            listNode *ln;
