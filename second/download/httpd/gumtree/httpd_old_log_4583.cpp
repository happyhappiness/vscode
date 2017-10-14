ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                          "error while decoding the session, "
                          "session not loaded: %s", r->uri);