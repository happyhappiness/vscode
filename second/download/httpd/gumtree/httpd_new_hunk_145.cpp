
        /* We're cool with filtering this. */
        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->buffer = apr_palloc(r->pool, c->bufferSize);

        zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
                           c->windowSize, c->memlevel,
                           Z_DEFAULT_STRATEGY);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
