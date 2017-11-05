ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02141) "parent: child %s",
                          (rv == APR_CHILD_DONE) ? "done" : "notdone");