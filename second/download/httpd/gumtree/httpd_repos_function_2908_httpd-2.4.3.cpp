static void add_vary(ap_expr_eval_ctx_t *ctx, const char *name)
{
    if (!ctx->vary_this)
        return;

    if (*ctx->vary_this) {
        *ctx->vary_this = apr_pstrcat(ctx->p, *ctx->vary_this, ", ", name,
                                      NULL);
    }
    else {
        *ctx->vary_this = name;
    }
}