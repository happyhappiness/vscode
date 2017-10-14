ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, SESSION_PREFIX
                          "attempt made to save the session twice, "
                          "session not saved: %s", r->uri);