    int eos = 0; /* non-zero once EOS is seen */

    /* Create the context which will be passed to the input filter;
     * containing a setaside pool and a brigade which constrain the
     * lifetime of the buffered data. */
    ctx = apr_palloc(r->pool, sizeof *ctx);
    ctx->bb = apr_brigade_create(r->pool, c->bucket_alloc);

    /* ... and a temporary brigade. */
    tempb = apr_brigade_create(r->pool, c->bucket_alloc);

    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c, "filling buffer, max size "
                  "%" APR_SIZE_T_FMT " bytes", maxlen);

    do {
        apr_status_t rv;
        apr_bucket *e, *next;

