static const char *unescape_func(ap_expr_eval_ctx_t *ctx, const void *data,
                                 const char *arg)
{
    char *result = apr_pstrdup(ctx->p, arg);
    int ret = ap_unescape_url_keep2f(result, 0);
    if (ret == OK)
        return result;
    ap_log_rerror(LOG_MARK(ctx->info), APLOG_DEBUG, 0, ctx->r, APLOGNO(00538)
                  "%s %% escape in unescape('%s') at %s:%d",
                  ret == HTTP_BAD_REQUEST ? "Bad" : "Forbidden", arg,
                  ctx->info->filename, ctx->info->line_number);
    return "";
}