                                pidfile, (long)getpid());
        }

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                    "caught SIGTERM, shutting down");

        return 1;
    } else if (shutdown_pending) {
        /* Time to perform a graceful shut down:
         * Reap the inactive children, and ask the active ones
         * to close their listeners, then wait until they are
         * all done to exit.
         */
