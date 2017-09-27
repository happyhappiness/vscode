ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01100)
                          "Ignoring bogus HTTP header returned by %s (%s)",
                          r->uri, r->method);