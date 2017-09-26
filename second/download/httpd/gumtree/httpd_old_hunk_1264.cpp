            }
        }
        /* Moved the fixups of Date headers and those affected by
         * ProxyPassReverse/etc from here to ap_proxy_read_headers
         */

        if ((r->status == 401) && (conf->error_override)) {
            const char *buf;
            const char *wa = "WWW-Authenticate";
            if ((buf = apr_table_get(r->headers_out, wa))) {
                apr_table_set(r->err_headers_out, wa, buf);
            } else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
