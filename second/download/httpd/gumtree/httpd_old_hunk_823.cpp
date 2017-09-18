            if ((buf = apr_table_get(r->headers_out, "URI")) != NULL) {
                apr_table_set(r->headers_out, "URI",
                              ap_proxy_location_reverse_map(r, conf, buf));
            }
        }

        r->sent_bodyct = 1;
        /* Is it an HTTP/0.9 response? If so, send the extra data */
        if (backasswards) {
            apr_ssize_t cntr = len;
            e = apr_bucket_heap_create(buffer, cntr, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
