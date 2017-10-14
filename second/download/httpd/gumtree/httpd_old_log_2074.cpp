ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Performing full renegotiation: complete handshake "
                          "protocol (%s support secure renegotiation)",
                          reneg_support);