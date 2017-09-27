        int folded = 0;

        field = NULL;
        rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
                         &len, r, 0, bb);

        /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
         * finding the end-of-line.  This is only going to happen if it
         * exceeds the configured limit for a field size.
         */
        if (rv == APR_ENOSPC && field) {
            r->status = HTTP_BAD_REQUEST;
            /* insure ap_escape_html will terminate correctly */
            field[len - 1] = '\0';
            apr_table_setn(r->notes, "error-notes",
                           apr_psprintf(r->pool,
                                       "Size of a request header field "
                                       "exceeds server limit.<br />\n"
                                        "<pre>\n%.*s\n</pre>/n",
                                        field_name_len(field), 
                                        ap_escape_html(r->pool, field)));
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
                          "Request header exceeds LimitRequestFieldSize: "
                          "%.*s", field_name_len(field), field);
            return;
        }

        if (rv != APR_SUCCESS) {
            r->status = HTTP_BAD_REQUEST;
            return;
        }

        if (last_field != NULL) {
            if ((len > 0) && ((*field == '\t') || *field == ' ')) {
                /* This line is a continuation of the preceding line(s),
