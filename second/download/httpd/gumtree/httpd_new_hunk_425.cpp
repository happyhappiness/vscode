            ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                         "proxy: previous connection is closed, creating a new connection.");
            new = 1;
        }
    }
    if (new) {
        int rc;

        /* create a new socket */
        backend->connection = NULL;

        /*
         * At this point we have a list of one or more IP addresses of
