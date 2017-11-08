int ssl_io_buffer_fill(request_rec *r, apr_size_t maxlen)
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

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "filling buffer, max size "
                  "%" APR_SIZE_T_FMT " bytes", maxlen);

    do {
        apr_status_t rv;
        apr_bucket *e, *next;

        /* The request body is read from the protocol-level input
         * filters; the buffering filter will reinject it from that
         * level, allowing content/resource filters to run later, if
         * necessary. */

        rv = ap_get_brigade(r->proto_input_filters, tempb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, 8192);
        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "could not read request body for SSL buffer");
            return ap_map_http_request_error(rv, HTTP_INTERNAL_SERVER_ERROR);
        }

        /* Iterate through the returned brigade: setaside each bucket
         * into the context's pool and move it into the brigade. */
        for (e = APR_BRIGADE_FIRST(tempb);
             e != APR_BRIGADE_SENTINEL(tempb) && !eos; e = next) {
            const char *data;
            apr_size_t len;

            next = APR_BUCKET_NEXT(e);

            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
            } else if (!APR_BUCKET_IS_METADATA(e)) {
                rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "could not read bucket for SSL buffer");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                total += len;
            }

            rv = apr_bucket_setaside(e, ctx->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "could not setaside bucket for SSL buffer");
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
        }

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                      total, eos);

        /* Fail if this exceeds the maximum buffer size. */
        if (total > maxlen) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request body exceeds maximum size (%" APR_SIZE_T_FMT 
                          ") for SSL buffer", maxlen);
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

    } while (!eos);

    apr_brigade_destroy(tempb);

    /* After consuming all protocol-level input, remove all protocol-level
     * filters.  It should strictly only be necessary to remove filters
     * at exactly ftype == AP_FTYPE_PROTOCOL, since this filter will 
     * precede all > AP_FTYPE_PROTOCOL anyway. */
    while (r->proto_input_filters->frec->ftype < AP_FTYPE_CONNECTION) {
        ap_remove_input_filter(r->proto_input_filters);
    }

    /* Insert the filter which will supply the buffered content. */
    ap_add_input_filter(ssl_io_buffer, ctx, r, c);

    return 0;
}