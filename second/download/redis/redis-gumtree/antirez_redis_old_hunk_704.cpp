        } else {
            /* No way, we need to wait for the next BGSAVE in order to
             * register differences. */
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
        }

