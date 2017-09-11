         * children sockets. We need to wait for the next BGSAVE
         * in order to synchronize. */
        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
        serverLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
    } else {
        if (server.repl_diskless_sync) {
            /* Diskless replication RDB child is created inside
             * replicationCron() since we want to delay its start a
             * few seconds to wait for more slaves to arrive. */
            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
            if (server.repl_diskless_sync_delay)
                serverLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Ok we don't have a BGSAVE in progress, let's start one. */
            if (startBgsaveForReplication() != REDIS_OK) {
                serverLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
                return;
            }
