             */
            log_level = APLOG_DEBUG;
        }

        ap_log_error(APLOG_MARK, log_level, rv, ap_server_conf,
                     "connect to listener on %pI", ap_listeners->bind_addr);
    }

    /* Create the request string. We include a User-Agent so that
     * adminstrators can track down the cause of the odd-looking
     * requests in their logs.
     */
