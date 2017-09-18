        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                         "proxy: HTTP: received 100 CONTINUE");
        }

        /* we must accept 3 kinds of date, but generate only 1 kind of date */
        if ((buf = apr_table_get(r->headers_out, "Date")) != NULL) {
            apr_table_set(r->headers_out, "Date",
                          ap_proxy_date_canon(p, buf));
        }
        if ((buf = apr_table_get(r->headers_out, "Expires")) != NULL) {
            apr_table_set(r->headers_out, "Expires",
                          ap_proxy_date_canon(p, buf));
        }
        if ((buf = apr_table_get(r->headers_out, "Last-Modified")) != NULL) {
            apr_table_set(r->headers_out, "Last-Modified",
                          ap_proxy_date_canon(p, buf));
        }

        /* munge the Location and URI response headers according to
         * ProxyPassReverse
         */
        if ((buf = apr_table_get(r->headers_out, "Location")) != NULL) {
            apr_table_set(r->headers_out, "Location",
                          ap_proxy_location_reverse_map(r, conf, buf));
        }
        if ((buf = apr_table_get(r->headers_out, "Content-Location")) != NULL) {
            apr_table_set(r->headers_out, "Content-Location",
                          ap_proxy_location_reverse_map(r, conf, buf));
        }
        if ((buf = apr_table_get(r->headers_out, "URI")) != NULL) {
            apr_table_set(r->headers_out, "URI",
                          ap_proxy_location_reverse_map(r, conf, buf));
        }

        if ((r->status == 401) && (conf->error_override != 0)) {
            const char *wa = "WWW-Authenticate";
            if ((buf = apr_table_get(r->headers_out, wa))) {
                apr_table_set(r->err_headers_out, wa, buf);
            } else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: origin server sent 401 without WWW-Authenticate header");
