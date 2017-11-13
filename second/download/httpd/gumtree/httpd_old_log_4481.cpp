ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "proxy: " PROXY_FUNCTION ": error reading response "
                      "headers from %s:%u", conn->hostname, conn->port);