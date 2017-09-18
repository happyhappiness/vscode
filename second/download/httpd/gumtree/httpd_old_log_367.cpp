ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", p_conn->name);