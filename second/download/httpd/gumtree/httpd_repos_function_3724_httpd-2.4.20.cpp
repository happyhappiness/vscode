ap_expr_t *ap_expr_list_func_make(const char *name, const ap_expr_t *arg,
                                ap_expr_parse_ctx_t *ctx)
{
    ap_expr_t *info = ap_expr_info_make(AP_EXPR_FUNC_LIST, name, ctx, arg);
    if (!info)
        return NULL;

    info->node_op = op_ListFuncInfo;
    return ap_expr_make(op_ListFuncCall, info, arg, ctx);
}