static const char *expr_func_fn(ap_expr_eval_ctx_t *ctx, const void *data,
                                const char *arg)
{
    char *var = (char *)arg;

    return var ? ssl_var_lookup(ctx->p, ctx->s, ctx->c, ctx->r, var) : NULL;
}