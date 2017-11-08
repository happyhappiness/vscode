static const char *escape_func(ap_expr_eval_ctx_t *ctx, const void *data,
                               const char *arg)
{
    return ap_escape_uri(ctx->p, arg);
}