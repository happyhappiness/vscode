            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }


        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->buffer = apr_palloc(r->pool, c->bufferSize);
        ctx->libz_end_func = inflateEnd;
        ctx->validation_buffer = NULL;
        ctx->validation_buffer_length = 0;

        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            inflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            /*
             * Remove ourselves as it does not make sense to return:
             * We are not able to init libz and pass data down the chain
             * compressed.
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

        apr_table_unset(r->headers_out, "Content-Length");

        /* initialize inflate output buffer */
        ctx->stream.next_out = ctx->buffer;
        ctx->stream.avail_out = c->bufferSize;

        inflate_init = 0;
    }

    while (!APR_BRIGADE_EMPTY(bb))
    {
        const char *data;
        apr_bucket *b;
        apr_size_t len;

        e = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_EOS(e)) {
            /*
             * We are really done now. Ensure that we never return here, even
             * if a second EOS bucket falls down the chain. Thus remove
             * ourselves.
             */
            ap_remove_output_filter(f);
            /* should be zero already anyway */
            ctx->stream.avail_in = 0;
            /*
             * Flush the remaining data from the zlib buffers. It is correct
             * to use Z_SYNC_FLUSH in this case and not Z_FINISH as in the
             * deflate case. In the inflate case Z_FINISH requires to have a
             * large enough output buffer to put ALL data in otherwise it
             * fails, whereas in the deflate case you can empty a filled output
             * buffer and call it again until no more output can be created.
             */
            flush_libz_buffer(ctx, c, f->c->bucket_alloc, inflate, Z_SYNC_FLUSH,
                              UPDATE_CRC);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Inflated %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            if (ctx->validation_buffer_length == VALIDATION_SIZE) {
                unsigned long compCRC, compLen;
                compCRC = getLong(ctx->validation_buffer);
                if (ctx->crc != compCRC) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Zlib: Checksum of inflated stream invalid");
                    return APR_EGENERAL;
                }
                ctx->validation_buffer += VALIDATION_SIZE / 2;
                compLen = getLong(ctx->validation_buffer);
                if (ctx->stream.total_out != compLen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Zlib: Length of inflated stream invalid");
                    return APR_EGENERAL;
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Zlib: Validation bytes not present");
                return APR_EGENERAL;
            }

            inflateEnd(&ctx->stream);
            /* No need for cleanup any longer */
            apr_pool_cleanup_kill(r->pool, ctx, deflate_ctx_cleanup);

            /* Remove EOS from the old list, and insert into the new. */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /*
             * Okay, we've seen the EOS.
             * Time to pass it along down the chain.
             */
            return ap_pass_brigade(f->next, ctx->bb);
        }

        if (APR_BUCKET_IS_FLUSH(e)) {
            apr_status_t rv;

            /* flush the remaining data from the zlib buffers */
            zRC = flush_libz_buffer(ctx, c, f->c->bucket_alloc, inflate,
                                    Z_SYNC_FLUSH, UPDATE_CRC);
            if (zRC != Z_OK) {
                return APR_EGENERAL;
            }

            /* Remove flush bucket from old brigade anf insert into the new. */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
            rv = ap_pass_brigade(f->next, ctx->bb);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            continue;
        }

        /* read */
        apr_bucket_read(e, &data, &len, APR_BLOCK_READ);

        /* first bucket contains zlib header */
        if (!inflate_init++) {
            if (len < 10) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Insufficient data for inflate");
                return APR_EGENERAL;
            }
            else  {
