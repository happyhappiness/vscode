
    while (!APR_BRIGADE_EMPTY(bb))
    {
        const char *data;
        apr_bucket *b;
        apr_size_t len;

        e = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_EOS(e)) {
            char *buf;

            ctx->stream.avail_in = 0; /* should be zero already anyway */
            /* flush the remaining data from the zlib buffers */
            flush_libz_buffer(ctx, c, f->c->bucket_alloc, deflate, Z_FINISH,
                              NO_UPDATE_CRC);

            buf = apr_palloc(r->pool, VALIDATION_SIZE);
            putLong((unsigned char *)&buf[0], ctx->crc);
            putLong((unsigned char *)&buf[4], ctx->stream.total_in);

            b = apr_bucket_pool_create(buf, VALIDATION_SIZE, r->pool,
                                       f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Compressed %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            /* leave notes for logging */
