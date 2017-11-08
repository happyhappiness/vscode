static int ap_expr_eval_binary_op(ap_expr_eval_ctx_t *ctx,
                                  const ap_expr_t *info,
                                  const ap_expr_t *args)
{
    ap_expr_op_binary_t *op_func = (ap_expr_op_binary_t *)info->node_arg1;
    const void *data = info->node_arg2;
    const ap_expr_t *a1 = args->node_arg1;
    const ap_expr_t *a2 = args->node_arg2;

    AP_DEBUG_ASSERT(info->node_op == op_BinaryOpInfo);
    AP_DEBUG_ASSERT(args->node_op == op_BinaryOpArgs);
    AP_DEBUG_ASSERT(op_func != NULL);
    AP_DEBUG_ASSERT(data != NULL);
    return (*op_func)(ctx, data, ap_expr_eval_word(ctx, a1),
                      ap_expr_eval_word(ctx, a2));
}