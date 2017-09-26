    if (renegotiate && !renegotiate_quick
        && (apr_table_get(r->headers_in, "transfer-encoding")
            || (apr_table_get(r->headers_in, "content-length")
                && strcmp(apr_table_get(r->headers_in, "content-length"), "0")))
        && !r->expecting_100) {
        int rv;
        apr_size_t rsize;

        rsize = dc->nRenegBufferSize == UNSET ? DEFAULT_RENEG_BUFFER_SIZE :
                                                dc->nRenegBufferSize;
        if (rsize > 0) {
            /* Fill the I/O buffer with the request body if possible. */
            rv = ssl_io_buffer_fill(r, rsize);
        }
        else {
            /* If the reneg buffer size is set to zero, just fail. */
            rv = HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "could not buffer message body to allow "
                          "SSL renegotiation to proceed");
            return rv;
