serverLog(REDIS_NOTICE,
                "MASTER <-> SLAVE sync: receiving %lld bytes from master",
                (long long) server.repl_transfer_size);