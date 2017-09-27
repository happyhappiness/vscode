ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01106)
                              "bad HTTP/%d.%d header returned by %s (%s)",
                              major, minor, r->uri, r->method);