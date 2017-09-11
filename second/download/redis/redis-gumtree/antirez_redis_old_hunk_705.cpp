        /* There is an RDB child process but it is writing directly to
         * children sockets. We need to wait for the next BGSAVE
         * in order to synchronize. */
        c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");

    /* CASE 3: There is no BGSAVE is progress. */
