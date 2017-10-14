request_rec *ap_read_request(conn_rec *conn)
{
    request_rec *r;
    apr_pool_t *p;
    const char *expect;
    int access_status;
    apr_bucket_brigade *tmp_bb;

    apr_pool_create(&p, conn->pool);
    r = apr_pcalloc(p, sizeof(request_rec));
    r->pool            = p;
    r->connection      = conn;
    r->server          = conn->base_server;

    r->user            = NULL;
    r->ap_auth_type    = NULL;

    r->allowed_methods = ap_make_method_list(p, 2);

    r->headers_in      = apr_table_make(r->pool, 25);
    r->subprocess_env  = apr_table_make(r->pool, 25);
    r->headers_out     = apr_table_make(r->pool, 12);
    r->err_headers_out = apr_table_make(r->pool, 5);
    r->notes           = apr_table_make(r->pool, 5);

    r->request_config  = ap_create_request_config(r->pool);
    /* Must be set before we run create request hook */

    r->proto_output_filters = conn->output_filters;
    r->output_filters  = r->proto_output_filters;
    r->proto_input_filters = conn->input_filters;
    r->input_filters   = r->proto_input_filters;
    ap_run_create_request(r);
    r->per_dir_config  = r->server->lookup_defaults;

    r->sent_bodyct     = 0;                      /* bytect isn't for body */

    r->read_length     = 0;
    r->read_body       = REQUEST_NO_BODY;

    r->status          = HTTP_REQUEST_TIME_OUT;  /* Until we get a request */
    r->the_request     = NULL;

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
        return NULL;
    }

    if (!r->assbackwards) {
        ap_get_mime_headers_core(r, tmp_bb);
        if (r->status != HTTP_REQUEST_TIME_OUT) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request failed: error reading the headers");
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            return r;
        }
    }
    else {
        if (r->header_only) {
            /*
             * Client asked for headers only with HTTP/0.9, which doesn't send
             * headers! Have to dink things just to make sure the error message
             * comes through...
             */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "client sent invalid HTTP/0.9 request: HEAD %s",
                          r->uri);
            r->header_only = 0;
            r->status = HTTP_BAD_REQUEST;
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            apr_brigade_destroy(tmp_bb);
            return r;
        }
    }

    apr_brigade_destroy(tmp_bb);

    r->status = HTTP_OK;                         /* Until further notice. */

    /* update what we think the virtual host is based on the headers we've
     * now read. may update status.
     */
    ap_update_vhost_from_headers(r);

    /* we may have switched to another server */
    r->per_dir_config = r->server->lookup_defaults;

    if ((!r->hostname && (r->proto_num >= HTTP_VERSION(1, 1)))
        || ((r->proto_num == HTTP_VERSION(1, 1))
            && !apr_table_get(r->headers_in, "Host"))) {
        /*
         * Client sent us an HTTP/1.1 or later request without telling us the
         * hostname, either with a full URL or a Host: header. We therefore
         * need to (as per the 1.1 spec) send an error.  As a special case,
         * HTTP/1.1 mentions twice (S9, S14.23) that a request MUST contain
         * a Host: header, and the server MUST respond with 400 if it doesn't.
         */
        r->status = HTTP_BAD_REQUEST;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "client sent HTTP/1.1 request without hostname "
                      "(see RFC2616 section 14.23): %s", r->uri);
    }

    if (r->status != HTTP_OK) {
        ap_send_error_response(r, 0);
        ap_run_log_transaction(r);
        return r;
    }

    if (((expect = apr_table_get(r->headers_in, "Expect")) != NULL)
        && (expect[0] != '\0')) {
        /*
         * The Expect header field was added to HTTP/1.1 after RFC 2068
         * as a means to signal when a 100 response is desired and,
         * unfortunately, to signal a poor man's mandatory extension that
         * the server must understand or return 417 Expectation Failed.
         */
        if (strcasecmp(expect, "100-continue") == 0) {
            r->expecting_100 = 1;
        }
        else {
            r->status = HTTP_EXPECTATION_FAILED;
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);
            ap_send_error_response(r, 0);
            ap_run_log_transaction(r);
            return r;
        }
    }

    ap_add_input_filter_handle(ap_http_input_filter_handle,
                               NULL, r, r->connection);

    if ((access_status = ap_run_post_read_request(r))) {
        ap_die(access_status, r);
        ap_run_log_transaction(r);
        return NULL;
    }

    return r;
}