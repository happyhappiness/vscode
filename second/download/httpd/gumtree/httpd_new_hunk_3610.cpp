                    apr_bucket* b;
                    apr_bucket* bstart;
                    rv = apr_brigade_partition(ctx->bbsave, (p-ctx->buf),
                                               &bstart);
                    ap_assert(rv == APR_SUCCESS);
                    while (b = APR_BRIGADE_FIRST(ctx->bbsave), b != bstart) {
                        apr_bucket_delete(b);
                    }
                    ctx->bytes -= (p-ctx->buf);
                    ctx->buf = p ;
                    found = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01428)
                                  "Skipped to first <%s> element",
