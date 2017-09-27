        len = ap_getline(buffer, sizeof(buffer), rp, 0);
        if (len == 0) {
            /* handle one potential stray CRLF */
            len = ap_getline(buffer, sizeof(buffer), rp, 0);
        }
        if (len <= 0) {
            ap_proxy_http_cleanup(NULL, r, backend);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: error reading status line from remote "
                          "server %s", backend->hostname);
            return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                 "Error reading from remote server");
        }
