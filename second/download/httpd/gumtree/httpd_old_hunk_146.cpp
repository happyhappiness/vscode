            b = apr_bucket_pool_create(buf, 8, r->pool, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Compressed %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            if (c->noteName) {
                if (ctx->stream.total_in > 0) {
                    int total;

                    total = ctx->stream.total_out * 100 / ctx->stream.total_in;

                    apr_table_setn(r->notes, c->noteName,
                                   apr_itoa(r->pool, total));
                }
                else {
                    apr_table_setn(r->notes, c->noteName, "-");
                }
            }

            deflateEnd(&ctx->stream);

            /* Remove EOS from the old list, and insert into the new. */
            APR_BUCKET_REMOVE(e);
