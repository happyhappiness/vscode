static const char *toupper_func(ap_expr_eval_ctx_t *ctx, const void *data,
                                const char *arg)
{
    char *result = apr_pstrdup(ctx->p, arg);
    ap_str_toupper(result);
    return result;
}