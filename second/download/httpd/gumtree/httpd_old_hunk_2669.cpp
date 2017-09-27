                 * right now, but capture what is there.
                 */
                ctx->validation_buffer = apr_pcalloc(f->r->pool,
                                                     VALIDATION_SIZE);
                if (ctx->stream.avail_in > VALIDATION_SIZE) {
                    ctx->validation_buffer_length = VALIDATION_SIZE;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Zlib: %d bytes of garbage at the end of "
                                  "compressed stream.",
                                  ctx->stream.avail_in - VALIDATION_SIZE);
                } else if (ctx->stream.avail_in > 0) {
                           ctx->validation_buffer_length = ctx->stream.avail_in;
                }
