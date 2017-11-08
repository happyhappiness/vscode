static const char *expr_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    char *var = (char *)data;
    SSLConnRec *sslconn = ssl_get_effective_config(ctx->c);

    return sslconn ? ssl_var_lookup_ssl(ctx->p, sslconn, ctx->r, var) : NULL;
}