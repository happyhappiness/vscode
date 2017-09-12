serverLog(LL_NOTICE,
                "Replication backlog freed after %d seconds "
                "without connected slaves.",
                (int) server.repl_backlog_time_limit);