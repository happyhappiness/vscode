    if (cur_timeout != conn->base_server->timeout) {
        apr_socket_timeout_set(csd, conn->base_server->timeout);
        cur_timeout = conn->base_server->timeout;
    }

    if (!r->assbackwards) {
        const char *tenc;

        ap_get_mime_headers_core(r, tmp_bb);
        if (r->status != HTTP_OK) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "request failed: error reading the headers");
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            return r;
        }

        tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
        if (tenc) {
            /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
             * Section 3.3.3.3: "If a Transfer-Encoding header field is
             * present in a request and the chunked transfer coding is not
             * the final encoding ...; the server MUST respond with the 400
             * (Bad Request) status code and then close the connection".
             */
            if (!(strcasecmp(tenc, "chunked") == 0 /* fast path */
                    || ap_find_last_token(r->pool, tenc, "chunked"))) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "client sent unknown Transfer-Encoding "
                              "(%s): %s", tenc, r->uri);
                r->status = HTTP_BAD_REQUEST;
                conn->keepalive = AP_CONN_CLOSE;
                ap_send_error_response(r, 0);
                ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
                ap_run_log_transaction(r);
                apr_brigade_destroy(tmp_bb);
                return r;
            }

            /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
             * Section 3.3.3.3: "If a message is received with both a
             * Transfer-Encoding and a Content-Length header field, the
             * Transfer-Encoding overrides the Content-Length. ... A sender
             * MUST remove the received Content-Length field".
             */
            apr_table_unset(r->headers_in, "Content-Length");
        }
    }

    apr_brigade_destroy(tmp_bb);

    /* update what we think the virtual host is based on the headers we've
     * now read. may update status.
     */
    ap_update_vhost_from_headers(r);
    access_status = r->status;

    /* Toggle to the Host:-based vhost's timeout mode to fetch the
     * request body and send the response body, if needed.
     */
    if (cur_timeout != r->server->timeout) {
        apr_socket_timeout_set(csd, r->server->timeout);
