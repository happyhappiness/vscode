ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: " PROXY_FUNCTION ": sending data to "
                          "%s:%u failed", conn->hostname, conn->port);