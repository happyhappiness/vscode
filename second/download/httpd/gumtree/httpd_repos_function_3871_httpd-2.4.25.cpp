static const char *ap_expr_eval_var(ap_expr_eval_ctx_t *ctx,
                                    ap_expr_var_func_t *func,
                                    const void *data)
{
    AP_DEBUG_ASSERT(func != NULL);
    AP_DEBUG_ASSERT(data != NULL);
    return (*func)(ctx, data);
}