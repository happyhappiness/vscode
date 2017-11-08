static int ap_expr_eval_unary_op(ap_expr_eval_ctx_t *ctx, const ap_expr_t *info,
                                 const ap_expr_t *arg)
{
    ap_expr_op_unary_t *op_func = (ap_expr_op_unary_t *)info->node_arg1;
    const void *data = info->node_arg2;

    AP_DEBUG_ASSERT(info->node_op == op_UnaryOpInfo);
    AP_DEBUG_ASSERT(op_func != NULL);
    AP_DEBUG_ASSERT(data != NULL);
    return (*op_func)(ctx, data, ap_expr_eval_word(ctx, arg));
}