        while((ln = listNext(&li))) {
            client *slave = ln->value;

            if (slave->replstate != REDIS_REPL_ONLINE) continue;
            if (slave->flags & REDIS_PRE_PSYNC) continue;
            if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
            {
                serverLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
                    replicationGetSlaveName(slave));
                freeClient(slave);
            }
