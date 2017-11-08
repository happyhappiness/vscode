ap_expr_t *ap_expr_make(ap_expr_node_op_e op, const void *a1, const void *a2,
                      ap_expr_parse_ctx_t *ctx)
{
    ap_expr_t *node = apr_palloc(ctx->pool, sizeof(ap_expr_t));
    node->node_op   = op;
    node->node_arg1 = a1;
    node->node_arg2 = a2;
    return node;
}