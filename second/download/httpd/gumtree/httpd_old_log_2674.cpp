ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", backend->hostname);