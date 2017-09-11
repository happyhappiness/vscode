            if (slave->flags & REDIS_PRE_PSYNC) continue;
            if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
            {
                redisLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
                    replicationGetSlaveName(slave));
                freeClient(slave);
            }
