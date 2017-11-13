ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Failed to set r->user to '%s'", dc->szUserName);