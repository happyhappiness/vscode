static const char *expr_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    char *var = (char *)data;
    return ssl_var_lookup_ssl(ctx->p, ctx->c, ctx->r, var);
}