static ap_expr_t *ap_expr_info_make(int type, const char *name,
                                  ap_expr_parse_ctx_t *ctx,
                                  const ap_expr_t *arg)
{
    ap_expr_t *info = apr_palloc(ctx->pool, sizeof(ap_expr_t));
    ap_expr_lookup_parms parms;
    parms.type  = type;
    parms.flags = ctx->flags;
    parms.pool  = ctx->pool;
    parms.ptemp = ctx->ptemp;
    parms.name  = name;
    parms.func  = &info->node_arg1;
    parms.data  = &info->node_arg2;
    parms.err   = &ctx->error2;
    parms.arg   = (arg && arg->node_op == op_String) ? arg->node_arg1 : NULL;
    if (ctx->lookup_fn(&parms) != OK)
        return NULL;
    return info;
}