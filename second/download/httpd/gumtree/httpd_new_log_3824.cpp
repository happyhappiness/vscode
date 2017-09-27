ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01337)
                      "Could not parse expr \"%s\" in %s: %s", expr,
                      ctx->r->filename, err);