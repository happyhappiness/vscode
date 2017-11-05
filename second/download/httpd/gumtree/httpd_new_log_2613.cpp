ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                              "request authorized without authentication by "
                              "access_checker_ex hook: %s", r->uri);