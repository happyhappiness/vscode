            /* Target is disk (or the slave is not capable of supporting
             * diskless replication) and we don't have a BGSAVE in progress,
             * let's start one. */
            serverLog(LL_NOTICE,"No BGSAVE in progress. Starting one ASAP");
        }
    }

