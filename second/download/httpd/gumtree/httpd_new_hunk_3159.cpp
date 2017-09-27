    ssl_filter_ctx_t *filter_ctx;

    filter_ctx = apr_palloc(c->pool, sizeof(ssl_filter_ctx_t));

    filter_ctx->config          = myConnConfig(c);

    ap_add_output_filter(ssl_io_coalesce, NULL, r, c);

    filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                       filter_ctx, r, c);

    filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
    filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);

