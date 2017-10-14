ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Illegal attempt to re-initialise SSL for server "
                "(SSLEngine On should go in the VirtualHost, not in global scope.)");