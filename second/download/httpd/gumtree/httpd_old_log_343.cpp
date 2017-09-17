ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_INFO, r->server,
                        ref ? "Spelling fix: %s: %d candidates from %s"
                        : "Spelling fix: %s: %d candidates",
                        r->uri, candidates->nelts, ref);