    return (root ? root->value : 0);
}

/* same as above, but use common ap_expr syntax / API */
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
