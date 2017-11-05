ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring server certificate chain "
                 "(%d CA certificate%s)",
                 n, n == 1 ? "" : "s");