    apr_pool_create(&ctx->pool, r->pool);
    ctx->bb = apr_brigade_create(ctx->pool, c->bucket_alloc);

    /* ... and a temporary brigade. */
    tempb = apr_brigade_create(r->pool, c->bucket_alloc);

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "filling buffer, max size "
                  "%" APR_SIZE_T_FMT " bytes", maxlen);

    do {
        apr_status_t rv;
        apr_bucket *e, *next;

        /* The request body is read from the protocol-level input
