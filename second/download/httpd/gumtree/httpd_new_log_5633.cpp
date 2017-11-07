ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                         ref ? APLOGNO(03226) "Spelling fix: %s: %d candidates from %s"
                             : APLOGNO(03227) "Spelling fix: %s: %d candidates%s",
                         r->uri, candidates->nelts,
                         (ref ? ref : ""));