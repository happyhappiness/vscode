ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "missing directive "
                          "name in parsed document %s", ctx->r->filename);