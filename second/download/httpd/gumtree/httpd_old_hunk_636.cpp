         */
        if (rv == APR_ENOSPC && field) {
            r->status = HTTP_BAD_REQUEST;
            /* insure ap_escape_html will terminate correctly */
            field[len - 1] = '\0';
            apr_table_setn(r->notes, "error-notes",
                           apr_pstrcat(r->pool,
                                       "Size of a request header field "
                                       "exceeds server limit.<br />\n"
                                       "<pre>\n",
                                       ap_escape_html(r->pool, field),
                                       "</pre>\n", NULL));
            return;
        }

        if (rv != APR_SUCCESS) {
            r->status = HTTP_BAD_REQUEST;
            return;
