ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
                          "error while encoding the session, "
                          "session not saved: %s", r->uri);