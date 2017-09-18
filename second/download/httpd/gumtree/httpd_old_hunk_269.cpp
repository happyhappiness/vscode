            p_conn->close += 1;
        }

        if ( r->status != HTTP_CONTINUE ) {
            received_continue = 0;
        } else {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, NULL,
                         "proxy: HTTP: received 100 CONTINUE");
        }

        /* we must accept 3 kinds of date, but generate only 1 kind of date */
        {
            const char *buf;
