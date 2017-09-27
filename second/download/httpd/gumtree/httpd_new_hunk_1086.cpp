    tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
    if (tenc && (strcasecmp(tenc, "chunked") == 0)) {
        /* The AJP protocol does not want body data yet */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: request is chunked");
    } else {
        /* Get client provided Content-Length header */
        content_length = get_content_length(r);
        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                maxsize - AJP_HEADER_SZ);

        if (status != APR_SUCCESS) {
            /* We had a failure: Close connection to backend */
