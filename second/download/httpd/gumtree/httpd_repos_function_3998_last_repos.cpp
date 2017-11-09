ap_expr_t *ap_expr_unary_op_make(const char *name, const ap_expr_t *arg,
                               ap_expr_parse_ctx_t *ctx)
{
    ap_expr_t *info = ap_expr_info_make(AP_EXPR_FUNC_OP_UNARY, name, ctx, arg);
    if (!info)
        return NULL;

    info->node_op = op_UnaryOpInfo;
    return ap_expr_make(op_UnaryOpCall, info, arg, ctx);
}