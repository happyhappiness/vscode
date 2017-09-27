    tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    /* Get the request... */
    if (!read_request_line(r, tmp_bb)) {
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request failed: URI too long");
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            return r;
        }

        apr_brigade_destroy(tmp_bb);
