ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00028)
                                  "No authentication done but request not "
                                  "allowed without authentication for %s. "
                                  "Authentication not configured?",
                                  r->uri);