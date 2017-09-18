ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "incomplete configuration: src %s, dst %s",
                          dc->charset_source ? dc->charset_source : "unspecified",
                          dc->charset_default ? dc->charset_default : "unspecified");