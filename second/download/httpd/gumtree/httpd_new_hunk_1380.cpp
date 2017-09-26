             * exceeds the configured limit for a field size.
             */
            if (rv == APR_ENOSPC && field) {
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
            }
            return;
        }

        if (last_field != NULL) {
            if ((len > 0) && ((*field == '\t') || *field == ' ')) {
