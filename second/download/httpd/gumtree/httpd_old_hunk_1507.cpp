    mod_filter_ctx *ctx = apr_pcalloc(r->pool, sizeof(mod_filter_ctx));
    ap_set_module_config(r->request_config, &filter_module, ctx);
#endif

    for (p = cfg->chain; p; p = p->next) {
        filter = apr_hash_get(cfg->live_filters, p->fname, APR_HASH_KEY_STRING);
        ap_add_output_filter_handle(filter, NULL, r, r->connection);
#ifndef NO_PROTOCOL
        if (ranges && (filter->proto_flags
                       & (AP_FILTER_PROTO_NO_BYTERANGE
                          | AP_FILTER_PROTO_CHANGE_LENGTH))) {
            ctx->range = apr_table_get(r->headers_in, "Range");
