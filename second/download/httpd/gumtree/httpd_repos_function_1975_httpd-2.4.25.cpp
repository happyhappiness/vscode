static const char *hc_expr_func_fn(ap_expr_eval_ctx_t *ctx, const void *data,
                                const char *arg)
{
    char *var = (char *)arg;

    if (var && *var && ctx->r && strcasecmp(var, "BODY") == 0) {
        return hc_get_body(ctx->r);
    }
    return NULL;
}