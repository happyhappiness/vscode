BOOL ssl_expr_eval(request_rec *r, ssl_expr *node)
{
    switch (node->node_op) {
        case op_True: {
            return TRUE;
        }
        case op_False: {
            return FALSE;
        }
        case op_Not: {
            ssl_expr *e = (ssl_expr *)node->node_arg1;
            return (!ssl_expr_eval(r, e));
        }
        case op_Or: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval(r, e1) || ssl_expr_eval(r, e2));
        }
        case op_And: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval(r, e1) && ssl_expr_eval(r, e2));
        }
        case op_Comp: {
            ssl_expr *e = (ssl_expr *)node->node_arg1;
            return ssl_expr_eval_comp(r, e);
        }
        default: {
            ssl_expr_error = "Internal evaluation error: Unknown expression node";
            return FALSE;
        }
    }
}