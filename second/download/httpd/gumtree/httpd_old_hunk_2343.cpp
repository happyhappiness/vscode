    int i;
    const char *te = NULL;
    int original_status = r->status;
    int proxy_status = OK;
    const char *original_status_line = r->status_line;
    const char *proxy_status_line = NULL;

    bb = apr_brigade_create(p, c->bucket_alloc);
    pass_bb = apr_brigade_create(p, c->bucket_alloc);

    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    rp = ap_proxy_make_fake_req(origin, r);
