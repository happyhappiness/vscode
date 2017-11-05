ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: %s Transfer-Encoding is not supported",
                     old_te_val);