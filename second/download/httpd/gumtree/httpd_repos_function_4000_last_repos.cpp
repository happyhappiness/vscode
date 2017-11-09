ap_expr_t *ap_expr_var_make(const char *name, ap_expr_parse_ctx_t *ctx)
{
    ap_expr_t *node = ap_expr_info_make(AP_EXPR_FUNC_VAR, name, ctx, NULL);
    if (!node)
        return NULL;

    node->node_op = op_Var;
    return node;
}