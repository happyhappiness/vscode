ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
                      "session is enabled but no session modules have been configured, "
                      "session not loaded: %s", r->uri);