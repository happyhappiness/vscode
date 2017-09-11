                serverLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Ok we don't have a BGSAVE in progress, let's start one. */
            if (startBgsaveForReplication() != C_OK) {
                serverLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
                return;
