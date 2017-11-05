ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, stat, p,
                      "make_sock: unable to listen for connections "
                      "on address %pI",
                      server->bind_addr);