ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02466)
                    "cache: response status to '%s' method is %d (>299), not invalidating cached entity: %s", r->method, r->status, r->uri);