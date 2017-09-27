ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": Found %s: %s - "
                          "preparing subrequest.",
                          conf->sendfile, location);