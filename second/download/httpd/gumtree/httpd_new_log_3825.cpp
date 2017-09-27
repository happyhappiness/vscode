ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01338)
                      "Could not evaluate expr \"%s\" in %s: %s", expr,
                      ctx->r->filename, ctx->intern->expr_err);