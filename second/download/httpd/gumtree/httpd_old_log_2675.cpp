ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, LOG_PREFIX "form auth cannot be used for proxy "
                      "requests due to XSS risk, access denied: %s", r->uri);