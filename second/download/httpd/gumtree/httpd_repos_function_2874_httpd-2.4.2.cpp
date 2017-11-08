static const char *ap_expr_eval_string_func(ap_expr_eval_ctx_t *ctx,
                                            const ap_expr_t *info,
                                            const ap_expr_t *arg)
{
    ap_expr_string_func_t *func = (ap_expr_string_func_t *)info->node_arg1;
    const void *data = info->node_arg2;

    AP_DEBUG_ASSERT(info->node_op == op_StringFuncInfo);
    AP_DEBUG_ASSERT(func != NULL);
    AP_DEBUG_ASSERT(data != NULL);
    return (*func)(ctx, data, ap_expr_eval_word(ctx, arg));
}