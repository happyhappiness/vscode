ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01099)
                                       "No HTTP headers returned by %s (%s)",
                                       r->uri, r->method);