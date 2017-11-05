ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p,
                      "make_sock: could not bind to address %pI",
                      server->bind_addr);