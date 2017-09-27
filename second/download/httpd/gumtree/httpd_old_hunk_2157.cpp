    filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                   filter_ctx, NULL, c);

    filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
    filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);

    ssl_io_input_add_filter(filter_ctx, c, ssl);

    SSL_set_bio(ssl, filter_ctx->pbioRead, filter_ctx->pbioWrite);
    filter_ctx->pssl            = ssl;

    apr_pool_cleanup_register(c->pool, (void*)filter_ctx,
