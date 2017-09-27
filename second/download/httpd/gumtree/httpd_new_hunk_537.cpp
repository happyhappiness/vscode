        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Changed client verification locations will force "
                     "renegotiation");
    }
#endif /* HAVE_SSL_SET_CERT_STORE */

    /* If a renegotiation is now required for this location, and the
     * request includes a message body (and the client has not
     * requested a "100 Continue" response), then the client will be
     * streaming the request body over the wire already.  In that
     * case, it is not possible to stop and perform a new SSL
     * handshake immediately; once the SSL library moves to the
     * "accept" state, it will reject the SSL packets which the client
     * is sending for the request body.
     * 
     * To allow authentication to complete in this auth hook, the
     * solution used here is to fill a (bounded) buffer with the
     * request body, and then to reinject that request body later.
     */
    if (renegotiate && !renegotiate_quick
        && (apr_table_get(r->headers_in, "transfer-encoding")
            || (apr_table_get(r->headers_in, "content-length")
                && strcmp(apr_table_get(r->headers_in, "content-length"), "0")))
        && !r->expecting_100) {
        int rv;

        /* Fill the I/O buffer with the request body if possible. */
        rv = ssl_io_buffer_fill(r);

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "could not buffer message body to allow "
                          "SSL renegotiation to proceed");
            return rv;
        }
    }

    /*
     * now do the renegotiation if anything was actually reconfigured
     */
    if (renegotiate) {
