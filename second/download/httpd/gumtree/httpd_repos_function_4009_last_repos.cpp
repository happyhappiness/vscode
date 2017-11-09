static const char *tolower_func(ap_expr_eval_ctx_t *ctx, const void *data,
                                const char *arg)
{
    char *result = apr_pstrdup(ctx->p, arg);
    ap_str_tolower(result);
    return result;
}