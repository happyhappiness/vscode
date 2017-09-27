            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "proxy: error reading status line from remote "
                          "server %s:%d", backend->hostname, backend->port);
            if (APR_STATUS_IS_TIMEUP(rc)) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: read timeout");
                if (do_100_continue) {
                    return ap_proxyerror(r, HTTP_SERVICE_UNAVAILABLE, "Timeout on 100-Continue");
                }
            }
            /*
             * If we are a reverse proxy request shutdown the connection
             * WITHOUT ANY response to trigger a retry by the client
             * if allowed (as for idempotent requests).
             * BUT currently we should not do this if the request is the
