            r->status_line = "200 OK";
            backend->close += 1;
        }

        interim_response = ap_is_HTTP_INFO(r->status);
        if (interim_response) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                         "proxy: HTTP: received interim %d response",
                         r->status);
        }
        /* Moved the fixups of Date headers and those affected by
         * ProxyPassReverse/etc from here to ap_proxy_read_headers
         */

        if ((r->status == 401) && (conf->error_override)) {
