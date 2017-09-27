
        field = NULL;
        rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
                         &len, r, 0, bb);

        if (rv != APR_SUCCESS) {
            if (rv == APR_TIMEUP) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else {
                r->status = HTTP_BAD_REQUEST;
            }

            /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
             * finding the end-of-line.  This is only going to happen if it
             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC && field) {
                /* insure ap_escape_html will terminate correctly */
                field[len - 1] = '\0';
                apr_table_setn(r->notes, "error-notes",
                               apr_pstrcat(r->pool,
                                           "Size of a request header field "
                                           "exceeds server limit.<br />\n"
                                           "<pre>\n",
                                           ap_escape_html(r->pool, field),
                                           "</pre>\n", NULL));
            }
            return;
        }

        if (last_field != NULL) {
            if ((len > 0) && ((*field == '\t') || *field == ' ')) {
