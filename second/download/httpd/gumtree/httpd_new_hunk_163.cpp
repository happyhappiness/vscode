            b = apr_bucket_pool_create(buf, 8, r->pool, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Compressed %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            /* leave notes for logging */
            if (c->note_input_name) {
                apr_table_setn(r->notes, c->note_input_name,
                               (ctx->stream.total_in > 0)
                                ? apr_off_t_toa(r->pool,
                                                ctx->stream.total_in)
                                : "-");
            }

            if (c->note_output_name) {
                apr_table_setn(r->notes, c->note_output_name,
                               (ctx->stream.total_in > 0)
                                ? apr_off_t_toa(r->pool,
                                                ctx->stream.total_out)
                                : "-");
            }

            if (c->note_ratio_name) {
                apr_table_setn(r->notes, c->note_ratio_name,
                               (ctx->stream.total_in > 0)
                                ? apr_itoa(r->pool,
                                           (int)(ctx->stream.total_out
                                                 * 100
                                                 / ctx->stream.total_in))
                                : "-");
            }

            deflateEnd(&ctx->stream);

            /* Remove EOS from the old list, and insert into the new. */
            APR_BUCKET_REMOVE(e);
