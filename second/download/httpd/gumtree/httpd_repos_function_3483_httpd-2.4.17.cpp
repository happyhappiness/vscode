static int ssl_expr_eval_comp(ap_expr_eval_ctx_t *ctx, const ap_expr_t *node)
{
    const ap_expr_t *e1 = node->node_arg1;
    const ap_expr_t *e2 = node->node_arg2;
    switch (node->node_op) {
    case op_EQ:
    case op_STR_EQ:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) == 0);
    case op_NE:
    case op_STR_NE:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) != 0);
    case op_LT:
    case op_STR_LT:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <  0);
    case op_LE:
    case op_STR_LE:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <= 0);
    case op_GT:
    case op_STR_GT:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >  0);
    case op_GE:
    case op_STR_GE:
        return (strcmplex(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >= 0);
    default:
        return ap_expr_eval_comp(ctx, node);
    }
}