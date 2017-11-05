ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01818)
                          "attempt made to save the session twice, "
                          "session not saved: %s", r->uri);