static int find_code_page(request_rec *r)
{
    charset_dir_t *dc = ap_get_module_config(r->per_dir_config,
                                             &charset_lite_module);
    charset_req_t *reqinfo;
    charset_filter_ctx_t *input_ctx, *output_ctx;
    apr_status_t rv;

    if (dc->debug >= DBGLVL_FLOW) {
        ap_log_rerror(APLOG_MARK,APLOG_DEBUG, 0, r,
                      "uri: %s file: %s method: %d "
                      "imt: %s flags: %s%s%s %s->%s",
                      r->uri,
                      r->filename ? r->filename : "(none)",
                      r->method_number,
                      r->content_type ? r->content_type : "(unknown)",
                      r->main     ? "S" : "",    /* S if subrequest */
                      r->prev     ? "R" : "",    /* R if redirect */
                      r->proxyreq ? "P" : "",    /* P if proxy */
                      dc->charset_source, dc->charset_default);
    }

    /* If we don't have a full directory configuration, bail out.
     */
    if (!dc->charset_source || !dc->charset_default) {
        if (dc->debug >= DBGLVL_PMC) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "incomplete configuration: src %s, dst %s",
                          dc->charset_source ? dc->charset_source : "unspecified",
                          dc->charset_default ? dc->charset_default : "unspecified");
        }
        return DECLINED;
    }

    /* catch proxy requests */
    if (r->proxyreq) {
        return DECLINED;
    }

    /* mod_rewrite indicators */
    if (r->filename
        && (!strncmp(r->filename, "redirect:", 9)
            || !strncmp(r->filename, "gone:", 5)
            || !strncmp(r->filename, "passthrough:", 12)
            || !strncmp(r->filename, "forbidden:", 10))) {
        return DECLINED;
    }

    /* no translation when server and network charsets are set to the same value */
    if (!strcasecmp(dc->charset_source, dc->charset_default)) {
        return DECLINED;
    }

    /* Get storage for the request data and the output filter context.
     * We rarely need the input filter context, so allocate that separately.
     */
    reqinfo = (charset_req_t *)apr_pcalloc(r->pool,
                                           sizeof(charset_req_t) +
                                           sizeof(charset_filter_ctx_t));
    output_ctx = (charset_filter_ctx_t *)(reqinfo + 1);

    reqinfo->dc = dc;
    output_ctx->dc = dc;
    output_ctx->tmpbb = apr_brigade_create(r->pool, 
                                           r->connection->bucket_alloc);
    ap_set_module_config(r->request_config, &charset_lite_module, reqinfo);

    reqinfo->output_ctx = output_ctx;

    switch (r->method_number) {
    case M_PUT:
    case M_POST:
        /* Set up input translation.  Note: A request body can be included
         * with the OPTIONS method, but for now we don't set up translation
         * of it.
         */
        input_ctx = apr_pcalloc(r->pool, sizeof(charset_filter_ctx_t));
        input_ctx->bb = apr_brigade_create(r->pool,
                                           r->connection->bucket_alloc);
        input_ctx->tmp = apr_palloc(r->pool, INPUT_XLATE_BUF_SIZE);
        input_ctx->dc = dc;
        reqinfo->input_ctx = input_ctx;
        rv = apr_xlate_open(&input_ctx->xlate, dc->charset_source,
                            dc->charset_default, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "can't open translation %s->%s",
                          dc->charset_default, dc->charset_source);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        if (apr_xlate_sb_get(input_ctx->xlate, &input_ctx->is_sb) != APR_SUCCESS) {
            input_ctx->is_sb = 0;
        }
    }

    return DECLINED;
}