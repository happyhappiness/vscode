         * also save other headers, keep this logic.
         */
        save_table = apr_table_make(r->pool, num_headers + 2);
        apr_table_do(addit_dammit, save_table, r->headers_out,
                     "Set-Cookie", NULL);
        r->headers_out = save_table;
    }
    else {
        r->headers_out = NULL;
        num_headers = 0;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
           "ajp_unmarshal_response: Number of headers is = %d",
           num_headers);

    for (i = 0; i < (int)num_headers; i++) {
        apr_uint16_t name;
        const char *stringname;
        const char *value;
        rc  = ajp_msg_peek_uint16(msg, &name);
        if (rc != APR_SUCCESS) {
            return rc;
