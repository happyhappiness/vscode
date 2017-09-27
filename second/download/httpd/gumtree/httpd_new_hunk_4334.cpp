        eval_ctx->vary_this = &ctx->intern->expr_vary_this;
        eval_ctx->re_nmatch = AP_MAX_REG_MATCH;
        eval_ctx->re_pmatch = re->match;
        eval_ctx->re_source = &re->source;
    }

    eval_ctx->info = expr_info;
    ret = ap_expr_exec_ctx(eval_ctx);
    if (ret < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01338)
                      "Could not evaluate expr \"%s\" in %s: %s", expr,
                      ctx->r->filename, ctx->intern->expr_err);
        *was_error = 1;
