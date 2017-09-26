{
    conn_rec *c = r->connection;
    struct modssl_buffer_ctx *ctx;
    apr_bucket_brigade *tempb;
    apr_off_t total = 0; /* total length buffered */
    int eos = 0; /* non-zero once EOS is seen */

    /* Create the context which will be passed to the input filter;
     * containing a setaside pool and a brigade which constrain the
     * lifetime of the buffered data. */
    ctx = apr_palloc(r->pool, sizeof *ctx);
    apr_pool_create(&ctx->pool, r->pool);
    ctx->bb = apr_brigade_create(ctx->pool, c->bucket_alloc);

    /* ... and a temporary brigade. */
    tempb = apr_brigade_create(r->pool, c->bucket_alloc);

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "filling buffer");

    do {
        apr_status_t rv;
        apr_bucket *e, *next;

        /* The request body is read from the protocol-level input
