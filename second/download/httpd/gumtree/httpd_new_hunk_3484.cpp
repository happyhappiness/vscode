
    /* Begin by presuming any module can make its own path_info assumptions,
     * until some module interjects and changes the value.
     */
    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;

    r->useragent_addr = conn->client_addr;
    r->useragent_ip = conn->client_ip;

    tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    ap_run_pre_read_request(r, conn);

    /* Get the request... */
    if (!read_request_line(r, tmp_bb)) {
        if (r->status == HTTP_REQUEST_URI_TOO_LARGE
            || r->status == HTTP_BAD_REQUEST) {
            if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00565)
                              "request failed: URI too long (longer than %d)",
                              r->server->limit_req_line);
            }
            else if (r->method == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00566)
                              "request failed: invalid characters in URI");
            }
            ap_send_error_response(r, 0);
            ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            goto traceout;
