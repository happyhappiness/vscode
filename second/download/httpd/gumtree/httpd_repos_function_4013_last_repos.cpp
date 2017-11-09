static const char *unbase64_func(ap_expr_eval_ctx_t *ctx, const void *data,
                               const char *arg)
{
    return ap_pbase64decode(ctx->p, arg);
}