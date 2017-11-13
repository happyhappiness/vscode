ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
                          "attempt made to save a session when the session had already expired, "
                          "session not saved: %s", r->uri);