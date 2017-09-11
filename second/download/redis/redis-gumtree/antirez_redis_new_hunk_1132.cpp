             * shutdown or else the dataset will be lost. */
            if (server.aof_state == REDIS_AOF_WAIT_REWRITE) {
                serverLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
                return C_ERR;
            }
            serverLog(REDIS_WARNING,
                "There is a child rewriting the AOF. Killing it!");
