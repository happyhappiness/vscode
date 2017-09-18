ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
                      "make_sock: for address %pI, setsockopt: (SO_KEEPALIVE)",
                      server->bind_addr);