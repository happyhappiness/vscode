            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bkt)) {
                if (!ctx->done) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02481)
                                  "Encountered premature end-of-stream while inflating");
                    return APR_EGENERAL;
                }

                /* Move everything to the returning brigade. */
                APR_BUCKET_REMOVE(bkt);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, bkt);
