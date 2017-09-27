ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01370) "missing "
                          "argument name for value to tag %s in %s",
                          apr_pstrmemdup(ctx->r->pool, intern->directive,
                                         intern->directive_len),
                                         ctx->r->filename);