static request_rec *create_request_rec(apr_pool_t *p1, conn_rec *conn, const char *method)
{
    request_rec *r;
    apr_pool_t *p;
    apr_bucket_alloc_t *ba;
    apr_pool_create(&p, p1);
    apr_pool_tag(p, "request");
    r = apr_pcalloc(p, sizeof(request_rec));
    ba = apr_bucket_alloc_create(p);
    r->pool            = p;
    r->connection      = conn;
    r->connection->bucket_alloc = ba;
    r->server          = conn->base_server;

    r->user            = NULL;
    r->ap_auth_type    = NULL;

    r->allowed_methods = ap_make_method_list(p, 2);

    r->headers_in      = apr_table_make(r->pool, 25);
    r->trailers_in     = apr_table_make(r->pool, 5);
    r->subprocess_env  = apr_table_make(r->pool, 25);
    r->headers_out     = apr_table_make(r->pool, 12);
    r->err_headers_out = apr_table_make(r->pool, 5);
    r->trailers_out    = apr_table_make(r->pool, 5);
    r->notes           = apr_table_make(r->pool, 5);

    r->kept_body       = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    r->request_config  = ap_create_request_config(r->pool);
    /* Must be set before we run create request hook */

    r->proto_output_filters = conn->output_filters;
    r->output_filters  = r->proto_output_filters;
    r->proto_input_filters = conn->input_filters;
    r->input_filters   = r->proto_input_filters;
    r->per_dir_config  = r->server->lookup_defaults;

    r->sent_bodyct     = 0;                      /* bytect isn't for body */

    r->read_length     = 0;
    r->read_body       = REQUEST_NO_BODY;

    r->status          = HTTP_OK;  /* Until further notice */
    r->header_only     = 1;
    r->the_request     = NULL;

    /* Begin by presuming any module can make its own path_info assumptions,
     * until some module interjects and changes the value.
     */
    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;

    r->useragent_addr = conn->client_addr;
    r->useragent_ip = conn->client_ip;


    /* Time to populate r with the data we have. */
    r->method = method;
    /* Provide quick information about the request method as soon as known */
    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'G') {
        r->header_only = 0;
    }

    r->protocol = "HTTP/1.0";
    r->proto_num = HTTP_VERSION(1, 0);

    r->hostname = NULL;

    return r;
}