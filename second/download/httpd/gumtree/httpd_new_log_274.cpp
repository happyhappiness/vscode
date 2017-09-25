ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing argument "
                          "name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, ctx->directive,
                                         ctx->ctx->directive_length),
                                         ctx->r->filename);