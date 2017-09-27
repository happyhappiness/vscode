
                rv = ap_pass_brigade(f->next, ctx->tmpbb);
                apr_brigade_cleanup(ctx->tmpbb);

                if (rv != APR_SUCCESS) {
                    ctx->state = RATE_ERROR;
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01457)
                                  "rl: brigade pass failed.");
                    break;
                }
            }
        }
    }
