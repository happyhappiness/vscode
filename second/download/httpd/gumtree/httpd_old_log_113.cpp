ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                                 c->base_server,
                                 "Spurious SSL handshake interrupt [Hint: "
                                 "Usually just one of those OpenSSL "
                                 "confusions!?]");