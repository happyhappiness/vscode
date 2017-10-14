ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf, APLOGNO(02120)
                     "make_secure_socket: failed to get a socket for %s",
                     addr);