ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "failed to send 101 interim response for connection "
                      "upgrade");