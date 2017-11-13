ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FD: Unable to find configured flush "
                          "provider '%s'", flush_method);