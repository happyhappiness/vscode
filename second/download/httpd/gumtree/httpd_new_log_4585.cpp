ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01819)
                          "attempt made to save a session when the session had already expired, "
                          "session not saved: %s", r->uri);