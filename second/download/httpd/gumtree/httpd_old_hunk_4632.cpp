
    ap_add_output_filter(ssl_io_coalesce, NULL, r, c);

    filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                       filter_ctx, r, c);

    filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
    filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);

    /* write is non blocking for the benefit of async mpm */
    if (c->cs) {
        BIO_set_nbio(filter_ctx->pbioWrite, 1);
    }

