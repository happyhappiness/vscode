    } else {
        /* Successful write(2). If AOF was in error state, restore the
         * OK state and log the event. */
        if (server.aof_last_write_status == REDIS_ERR) {
            serverLog(REDIS_WARNING,
                "AOF write error looks solved, Redis can write again.");
            server.aof_last_write_status = REDIS_OK;
        }
    }
    server.aof_current_size += nwritten;
