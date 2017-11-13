ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(00067)
                      "make_sock: for address %pI, apr_socket_opt_set: (SO_REUSEADDR)",
                      server->bind_addr);