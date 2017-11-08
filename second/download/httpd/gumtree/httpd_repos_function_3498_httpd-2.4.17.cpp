static const char *osenv_func(ap_expr_eval_ctx_t *ctx, const void *data,
                              const char *arg)
{
    return getenv(arg);
}