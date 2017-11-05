ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                         ref ? "Spelling fix: %s: %d candidates from %s"
                             : "Spelling fix: %s: %d candidates%s",
                         r->uri, candidates->nelts,
                         (ref ? ref : ""));