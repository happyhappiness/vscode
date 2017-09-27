    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;

    tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    /* Get the request... */
    if (!read_request_line(r, tmp_bb)) {
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE
            || r->status == HTTP_BAD_REQUEST) {
            if (r->status == HTTP_BAD_REQUEST) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "request failed: invalid characters in URI");
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "request failed: URI too long (longer than %d)", r->server->limit_req_line);
            }
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            goto traceout;
        }
        else if (r->status == HTTP_REQUEST_TIME_OUT) {
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            if (!r->connection->keepalives) {
                ap_run_log_transaction(r);
            }
            apr_brigade_destroy(tmp_bb);
            goto traceout;
        }

        apr_brigade_destroy(tmp_bb);
        r = NULL;
        goto traceout;
    }

    /* We may have been in keep_alive_timeout mode, so toggle back
     * to the normal timeout mode as we fetch the header lines,
     * as necessary.
     */
