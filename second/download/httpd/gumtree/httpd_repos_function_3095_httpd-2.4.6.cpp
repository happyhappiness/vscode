ap_expr_t *ap_expr_binary_op_make(const char *name, const ap_expr_t *arg1,
                                const ap_expr_t *arg2, ap_expr_parse_ctx_t *ctx)
{
    ap_expr_t *args;
    ap_expr_t *info = ap_expr_info_make(AP_EXPR_FUNC_OP_BINARY, name, ctx,
                                        arg2);
    if (!info)
        return NULL;

    info->node_op = op_BinaryOpInfo;
    args = ap_expr_make(op_BinaryOpArgs, arg1, arg2, ctx);
    return ap_expr_make(op_BinaryOpCall, info, args, ctx);
}