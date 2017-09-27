         * we must ignore the Host header (RFC 2616 5.2).
         * To enforce this, we reset the Host header to the value from the
         * request line.
         */
        if (have_hostname_from_url && host_header != NULL) {
            const char *repl = construct_host_header(r, is_v6literal);
            apr_table_set(r->headers_in, "Host", repl);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02417)
                          "Replacing host header '%s' with host '%s' given "
                          "in the request uri", host_header, repl);
        }
    }

