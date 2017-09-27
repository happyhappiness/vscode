        }

        /* We're cool with filtering this. */
        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->buffer = apr_palloc(r->pool, c->bufferSize);
        ctx->libz_end_func = deflateEnd;

        zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
                           c->windowSize, c->memlevel,
                           Z_DEFAULT_STRATEGY);

        if (zRC != Z_OK) {
            deflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "unable to init Zlib: "
                          "deflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            /*
             * Remove ourselves as it does not make sense to return:
             * We are not able to init libz and pass data down the chain
             * uncompressed.
             */
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }
        /*
         * Register a cleanup function to ensure that we cleanup the internal
         * libz resources.
         */
        apr_pool_cleanup_register(r->pool, ctx, deflate_ctx_cleanup,
                                  apr_pool_cleanup_null);

        /* add immortal gzip header */
        e = apr_bucket_immortal_create(gzip_header, sizeof gzip_header,
                                       f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

