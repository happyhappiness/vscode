ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(02638)
                          "make_sock: for address %pI, apr_socket_opt_set: "
                          "(SO_REUSEPORT)",
                          server->bind_addr);