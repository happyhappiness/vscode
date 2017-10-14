ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "This resource does not accept the %s method.",
                              r->method);