ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(00069)
                          "make_sock: for address %pI, apr_socket_opt_set: "
                          "(IPV6_V6ONLY)",
                          server->bind_addr);