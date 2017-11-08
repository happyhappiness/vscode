static const char *env_func(ap_expr_eval_ctx_t *ctx, const void *data,
                            const char *arg)
{
    const char *res;
    /* this order is for ssl_expr compatibility */
    if (ctx->r) {
        if ((res = apr_table_get(ctx->r->notes, arg)) != NULL)
            return res;
        else if ((res = apr_table_get(ctx->r->subprocess_env, arg)) != NULL)
            return res;
    }
    return getenv(arg);
}