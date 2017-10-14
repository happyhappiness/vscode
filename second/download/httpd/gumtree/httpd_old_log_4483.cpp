ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": Internal redirect to %s",
                          req_conf->location);