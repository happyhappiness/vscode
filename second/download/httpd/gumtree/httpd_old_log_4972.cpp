ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p,
                          "make_sock: failed to set SendBufferSize for "
                          "address %pI, using default",
                          server->bind_addr);