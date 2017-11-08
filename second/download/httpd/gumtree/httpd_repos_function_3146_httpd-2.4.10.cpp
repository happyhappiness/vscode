static int ap_expr_eval(ap_expr_eval_ctx_t *ctx, const ap_expr_t *node)
{
    const ap_expr_t *e1 = node->node_arg1;
    const ap_expr_t *e2 = node->node_arg2;
    int result = FALSE;
    if (inc_rec(ctx))
        return result;
    while (1) {
        switch (node->node_op) {
        case op_True:
            result ^= TRUE;
            goto out;
        case op_False:
            result ^= FALSE;
            goto out;
        case op_Not:
            result = !result;
            node = e1;
            break;
        case op_Or:
            do {
                if (e1->node_op == op_Not) {
                    if (!ap_expr_eval(ctx, e1->node_arg1)) {
                        result ^= TRUE;
                        goto out;
                    }
                }
                else {
                    if (ap_expr_eval(ctx, e1)) {
                        result ^= TRUE;
                        goto out;
                    }
                }
                node = node->node_arg2;
                e1 = node->node_arg1;
            } while (node->node_op == op_Or);
            break;
        case op_And:
            do {
                if (e1->node_op == op_Not) {
                    if (ap_expr_eval(ctx, e1->node_arg1)) {
                        result ^= FALSE;
                        goto out;
                    }
                }
                else {
                    if (!ap_expr_eval(ctx, e1)) {
                        result ^= FALSE;
                        goto out;
                    }
                }
                node = node->node_arg2;
                e1 = node->node_arg1;
            } while (node->node_op == op_And);
            break;
        case op_UnaryOpCall:
            result ^= ap_expr_eval_unary_op(ctx, e1, e2);
            goto out;
        case op_BinaryOpCall:
            result ^= ap_expr_eval_binary_op(ctx, e1, e2);
            goto out;
        case op_Comp:
            if (ctx->info->flags & AP_EXPR_FLAG_SSL_EXPR_COMPAT)
                result ^= ssl_expr_eval_comp(ctx, e1);
            else
                result ^= ap_expr_eval_comp(ctx, e1);
            goto out;
        default:
            *ctx->err = "Internal evaluation error: Unknown expression node";
            goto out;
        }
        e1 = node->node_arg1;
        e2 = node->node_arg2;
    }
out:
    ctx->reclvl--;
    return result;
}