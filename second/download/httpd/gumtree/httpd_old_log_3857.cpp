ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: CONNECT: read %" APR_OFF_T_FMT
                          " bytes from %s", len, name);