request_rec *h2_request_create_rec(const h2_request *req, conn_rec *conn)
{
    request_rec *r;
    apr_pool_t *p;
    int access_status = HTTP_OK;    
    
    apr_pool_create(&p, conn->pool);
    apr_pool_tag(p, "request");
    r = apr_pcalloc(p, sizeof(request_rec));
    AP_READ_REQUEST_ENTRY((intptr_t)r, (uintptr_t)conn);
    r->pool            = p;
    r->connection      = conn;
    r->server          = conn->base_server;
    
    r->user            = NULL;
    r->ap_auth_type    = NULL;
    
    r->allowed_methods = ap_make_method_list(p, 2);
    
    r->headers_in      = apr_table_clone(r->pool, req->headers);
    r->trailers_in     = apr_table_make(r->pool, 5);
    r->subprocess_env  = apr_table_make(r->pool, 25);
    r->headers_out     = apr_table_make(r->pool, 12);
    r->err_headers_out = apr_table_make(r->pool, 5);
    r->trailers_out    = apr_table_make(r->pool, 5);
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
    
    r->status          = HTTP_OK;  /* Until further notice */
    r->header_only     = 0;
    r->the_request     = NULL;
    
    /* Begin by presuming any module can make its own path_info assumptions,
     * until some module interjects and changes the value.
     */
    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;
    
    r->useragent_addr = conn->client_addr;
    r->useragent_ip = conn->client_ip;
    
    ap_run_pre_read_request(r, conn);
    
    /* Time to populate r with the data we have. */
    r->request_time = req->request_time;
    r->method = req->method;
    /* Provide quick information about the request method as soon as known */
    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'H') {
        r->header_only = 1;
    }

    ap_parse_uri(r, req->path);
    r->protocol = "HTTP/2";
    r->proto_num = HTTP_VERSION(2, 0);

    r->the_request = apr_psprintf(r->pool, "%s %s %s", 
                                  r->method, req->path, r->protocol);
    
    /* update what we think the virtual host is based on the headers we've
     * now read. may update status.
     * Leave r->hostname empty, vhost will parse if form our Host: header,
     * otherwise we get complains about port numbers.
     */
    r->hostname = NULL;
    ap_update_vhost_from_headers(r);
    
    /* we may have switched to another server */
    r->per_dir_config = r->server->lookup_defaults;
    
    /*
     * Add the HTTP_IN filter here to ensure that ap_discard_request_body
     * called by ap_die and by ap_send_error_response works correctly on
     * status codes that do not cause the connection to be dropped and
     * in situations where the connection should be kept alive.
     */
    ap_add_input_filter_handle(ap_http_input_filter_handle,
                               NULL, r, r->connection);
    
    if (access_status != HTTP_OK
        || (access_status = ap_run_post_read_request(r))) {
        /* Request check post hooks failed. An example of this would be a
         * request for a vhost where h2 is disabled --> 421.
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn, APLOGNO()
                      "h2_request(%d): access_status=%d, request_create failed",
                      req->id, access_status);
        ap_die(access_status, r);
        ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
        ap_run_log_transaction(r);
        r = NULL;
        goto traceout;
    }
    
    AP_READ_REQUEST_SUCCESS((uintptr_t)r, (char *)r->method, 
                            (char *)r->uri, (char *)r->server->defn_name, 
                            r->status);
    return r;
traceout:
    AP_READ_REQUEST_FAILURE((uintptr_t)r);
    return r;
}