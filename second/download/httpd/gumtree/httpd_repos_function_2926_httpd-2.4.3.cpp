static const char *req_header_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    const char **varname = (const char **)data;
    int index = (varname - req_header_var_names);
    const char *name;

    AP_DEBUG_ASSERT(index < 6);
    if (!ctx->r)
        return "";

    name = req_header_header_names[index];
    add_vary(ctx, name);
    return apr_table_get(ctx->r->headers_in, name);
}