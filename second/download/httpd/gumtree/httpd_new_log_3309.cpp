ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf, APLOGNO(02121)
                         "make_secure_socket: for %s, WSAIoctl: "
                         "(SO_SSL_SET_FLAGS)", addr);