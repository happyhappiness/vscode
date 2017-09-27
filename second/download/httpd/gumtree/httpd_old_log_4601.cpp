ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": File subrequest to %s",
                          req_conf->location);