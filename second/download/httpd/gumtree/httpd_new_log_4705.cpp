ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01821)
                          "session is enabled but no session modules have been configured, "
                          "session not saved: %s", r->uri);