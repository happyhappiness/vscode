ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p, APLOGNO(00071)
                          "make_sock: failed to set ReceiveBufferSize for "
                          "address %pI, using default",
                          server->bind_addr);