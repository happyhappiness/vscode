ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "can't open translation %s->%s",
                          dc->charset_default, dc->charset_source);