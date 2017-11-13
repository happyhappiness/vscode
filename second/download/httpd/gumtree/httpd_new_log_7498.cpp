ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02569)
                     "Illegal attempt to re-initialise SSL for server "
                     "(SSLEngine On should go in the VirtualHost, not in global scope.)");