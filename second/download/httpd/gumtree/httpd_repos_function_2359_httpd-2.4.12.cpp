static const char *include_expr_var_fn(ap_expr_eval_ctx_t *eval_ctx,
                                       const void *data,
                                       const char *arg)
{
    const char *res, *name = data;
    include_ctx_t *ctx = eval_ctx->data;
    if ((name[0] == 'e') || (name[0] == 'E')) {
        /* keep legacy "env" semantics */
        if ((res = apr_table_get(ctx->r->notes, arg)) != NULL)
            return res;
        else if ((res = get_include_var(arg, ctx)) != NULL)
            return res;
        else
            return getenv(arg);
    }
    else {
        return get_include_var(arg, ctx);
    }
}