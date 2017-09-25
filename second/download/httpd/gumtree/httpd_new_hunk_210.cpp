            if ((buf = apr_table_get(r->headers_out, "URI")) != NULL) {
                apr_table_set(r->headers_out, "URI",
                              ap_proxy_location_reverse_map(r, conf, buf));
            }
        }

        if ((r->status == 401) && (conf->error_override != 0)) {
            const char *buf;
            const char *wa = "WWW-Authenticate";
            if ((buf = apr_table_get(r->headers_out, wa))) {
                apr_table_set(r->err_headers_out, wa, buf);
            } else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: origin server sent 401 without WWW-Authenticate header");
            }
        }

        r->sent_bodyct = 1;
        /* Is it an HTTP/0.9 response? If so, send the extra data */
        if (backasswards) {
            apr_ssize_t cntr = len;
            e = apr_bucket_heap_create(buffer, cntr, NULL, c->bucket_alloc);
