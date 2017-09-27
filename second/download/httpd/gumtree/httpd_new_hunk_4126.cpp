    }

    /* If anything remains in the brigade, it must now be passed down
     * the filter stack, first prepending anything that has been
     * coalesced. */
    if (ctx && ctx->bytes) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                      "coalesce: passing on %" APR_SIZE_T_FMT " bytes", ctx->bytes);

        e = apr_bucket_transient_create(ctx->buffer, ctx->bytes, bb->bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(bb, e);
        ctx->bytes = 0; /* buffer now emptied. */
