                }

                fb = apr_bucket_flush_create(ba);

                APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, fb);

#if 0
                brigade_dump(f->r, ctx->tmpbb);
                brigade_dump(f->r, bb);
#endif

                rv = ap_pass_brigade(f->next, ctx->tmpbb);
                apr_brigade_cleanup(ctx->tmpbb);

                if (rv != APR_SUCCESS) {
                    ctx->state = RATE_ERROR;
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, f->r, APLOGNO(01457)
                                  "rl: brigade pass failed.");
                    break;
                }
            }
