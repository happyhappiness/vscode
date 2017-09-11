            if (server.repl_diskless_sync_delay)
                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Target is disk and we don't have a BGSAVE in progress,
             * let's start one. */
            if (startBgsaveForReplication() != C_OK) {
                serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
