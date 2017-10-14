ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: FCGI: truncating environment to %d bytes and %d elements",
                          (int)bodylen, i);