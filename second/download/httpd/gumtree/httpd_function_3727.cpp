static int parse_ap_expr(include_ctx_t *ctx, const char *expr, int *was_error)
{
    ap_expr_info_t expr_info;
    const char *err;
    int ret;
    backref_t *re = ctx->intern->re;
    ap_expr_eval_ctx_t *eval_ctx = ctx->intern->expr_eval_ctx;

    expr_info.filename = ctx->r->filename;
    expr_info.line_number = 0;
    expr_info.module_index = APLOG_MODULE_INDEX;
    expr_info.flags = AP_EXPR_FLAG_RESTRICTED;
    err = ap_expr_parse(ctx->r->pool, ctx->r->pool, &expr_info, expr,
                        include_expr_lookup);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01337)
                      "Could not parse expr \"%s\" in %s: %s", expr,
                      ctx->r->filename, err);
        *was_error = 1;
        return 0;
    }

    if (!re) {
        ctx->intern->re = re = apr_pcalloc(ctx->pool, sizeof(*re));
    }
    else {
        /* ap_expr_exec_ctx() does not care about re->have_match but only about
         * re->source
         */
        if (!re->have_match)
            re->source = NULL;
    }

    if (!eval_ctx) {
        eval_ctx = apr_pcalloc(ctx->pool, sizeof(*eval_ctx));
        ctx->intern->expr_eval_ctx = eval_ctx;
        eval_ctx->r         = ctx->r;
        eval_ctx->c         = ctx->r->connection;
        eval_ctx->s         = ctx->r->server;
        eval_ctx->p         = ctx->r->pool;
        eval_ctx->data      = ctx;
        eval_ctx->err       = &ctx->intern->expr_err;
        eval_ctx->vary_this = &ctx->intern->expr_vary_this;
        eval_ctx->re_nmatch = AP_MAX_REG_MATCH;
        eval_ctx->re_pmatch = re->match;
        eval_ctx->re_source = &re->source;
    }

    eval_ctx->info = &expr_info;
    ret = ap_expr_exec_ctx(eval_ctx);
    if (ret < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(01338)
                      "Could not evaluate expr \"%s\" in %s: %s", expr,
                      ctx->r->filename, ctx->intern->expr_err);
        *was_error = 1;
        return 0;
    }
    *was_error = 0;
    if (re->source)
        re->have_match = 1;
    return ret;
}