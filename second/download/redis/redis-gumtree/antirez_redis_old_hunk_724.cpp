         * in order to synchronize. */
        c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
    } else {
        if (server.repl_diskless_sync) {
            /* Diskless replication RDB child is created inside
