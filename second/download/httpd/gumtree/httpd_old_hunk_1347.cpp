            r->status_line = apr_pstrdup(p, &buffer[9]);
            
            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            r->headers_out = ap_proxy_read_headers(r, rp, buffer,
                                                   sizeof(buffer), origin);
            if (r->headers_out == NULL) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             r->server, "proxy: bad HTTP/%d.%d header "
                             "returned by %s (%s)", major, minor, r->uri,
