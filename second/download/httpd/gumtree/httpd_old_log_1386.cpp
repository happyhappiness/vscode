ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "proxy: error reading status line from remote "
                          "server %s", backend->hostname);