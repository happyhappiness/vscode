            /* Set any repl_transfer_size to avoid entering this code path
             * at the next call. */
            server.repl_transfer_size = 0;
            serverLog(REDIS_NOTICE,
                "MASTER <-> SLAVE sync: receiving streamed RDB from master");
        } else {
            usemark = 0;
            server.repl_transfer_size = strtol(buf+1,NULL,10);
            serverLog(REDIS_NOTICE,
                "MASTER <-> SLAVE sync: receiving %lld bytes from master",
                (long long) server.repl_transfer_size);
        }
