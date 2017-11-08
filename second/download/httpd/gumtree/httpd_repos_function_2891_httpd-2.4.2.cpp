static const char *req_table_func(ap_expr_eval_ctx_t *ctx, const void *data,
                                  const char *arg)
{
    const char *name = (const char *)data;
    apr_table_t *t;
    if (!ctx->r)
        return "";

    if (name[2] == 's') {           /* resp */
        /* Try r->headers_out first, fall back on err_headers_out. */
        const char *v = apr_table_get(ctx->r->headers_out, arg);
        if (v) {
            return v;
        }
        t = ctx->r->err_headers_out;
    }
    else if (name[0] == 'n')        /* notes */
        t = ctx->r->notes;
    else if (name[3] == 'e')        /* reqenv */
        t = ctx->r->subprocess_env;
    else {                          /* req, http */
        t = ctx->r->headers_in;
        add_vary(ctx, arg);
    }
    return apr_table_get(t, arg);
}