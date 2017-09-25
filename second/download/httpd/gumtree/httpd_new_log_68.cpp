ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
                     "make_secure_socket: failed to get a socket for %s", 
                     addr);