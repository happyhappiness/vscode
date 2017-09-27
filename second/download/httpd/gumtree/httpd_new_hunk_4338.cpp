                }

                fb = apr_bucket_flush_create(ba);

                APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, fb);

                /*
                 * Adjust the burst amount depending on how much
                 * we've done up to now.
                 */
                if (ctx->burst) {
                    len = ctx->burst;
                    apr_brigade_length(ctx->tmpbb, 1, &len);
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                        APLOGNO(03485) "rl: burst %d; len %"APR_OFF_T_FMT, ctx->burst, len);
                    if (len < ctx->burst) {
                        ctx->burst -= len;
                    }
                    else {
                        ctx->burst = 0;
                    }
                }

#if defined(RLFDEBUG)
                brigade_dump(f->r, ctx->tmpbb);
                brigade_dump(f->r, bb);
#endif /* RLFDEBUG */

                rv = ap_pass_brigade(f->next, ctx->tmpbb);
                apr_brigade_cleanup(ctx->tmpbb);

                if (rv != APR_SUCCESS) {
                    /* Most often, user disconnects from stream */
                    ctx->state = RATE_ERROR;
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, f->r, APLOGNO(01457)
                                  "rl: brigade pass failed.");
                    break;
                }
            }
