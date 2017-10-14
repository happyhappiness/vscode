ap_log_perror(APLOG_MARK, APLOG_CRIT, status, pconf,
                                 "alloc_listener: failed to set up sockaddr for %s:%d", sl->addr, sl->port);