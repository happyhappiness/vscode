    if (cur_timeout != conn->base_server->timeout) {
        apr_socket_timeout_set(csd, conn->base_server->timeout);
        cur_timeout = conn->base_server->timeout;
    }

    if (!r->assbackwards) {
        ap_get_mime_headers_core(r, tmp_bb);
        if (r->status != HTTP_OK) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00567)
                          "request failed: error reading the headers");
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            goto traceout;
        }

        if (apr_table_get(r->headers_in, "Transfer-Encoding")
            && apr_table_get(r->headers_in, "Content-Length")) {
            /* 2616 section 4.4, point 3: "if both Transfer-Encoding
             * and Content-Length are received, the latter MUST be
             * ignored"; so unset it here to prevent any confusion
             * later. */
            apr_table_unset(r->headers_in, "Content-Length");
        }
    }
    else {
        if (r->header_only) {
            /*
