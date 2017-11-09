static const char *hc_expr_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    char *var = (char *)data;

    if (var && *var && ctx->r && strcasecmp(var, "BODY") == 0) {
        return hc_get_body(ctx->r);
    }
    return NULL;
}