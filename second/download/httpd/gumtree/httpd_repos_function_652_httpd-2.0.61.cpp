static BOOL ssl_expr_eval_comp(request_rec *r, ssl_expr *node)
{
    switch (node->node_op) {
        case op_EQ: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (strcmp(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) == 0);
        }
        case op_NE: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (strcmp(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) != 0);
        }
        case op_LT: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval_strcmplex(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) <  0);
        }
        case op_LE: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval_strcmplex(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) <= 0);
        }
        case op_GT: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval_strcmplex(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) >  0);
        }
        case op_GE: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            return (ssl_expr_eval_strcmplex(ssl_expr_eval_word(r, e1), ssl_expr_eval_word(r, e2)) >= 0);
        }
        case op_IN: {
            ssl_expr *e1 = (ssl_expr *)node->node_arg1;
            ssl_expr *e2 = (ssl_expr *)node->node_arg2;
            ssl_expr *e3;
            char *w1 = ssl_expr_eval_word(r, e1);
            BOOL found = FALSE;
            do {
                e3 = (ssl_expr *)e2->node_arg1;
                e2 = (ssl_expr *)e2->node_arg2;
                if (strcmp(w1, ssl_expr_eval_word(r, e3)) == 0) {
                    found = TRUE;
                    break;
                }
            } while (e2 != NULL);
            return found;
        }
        case op_REG: {
            ssl_expr *e1;
            ssl_expr *e2;
            char *word;
            regex_t *regex;

            e1 = (ssl_expr *)node->node_arg1;
            e2 = (ssl_expr *)node->node_arg2;
            word = ssl_expr_eval_word(r, e1);
            regex = (regex_t *)(e2->node_arg1);
            return (ap_regexec(regex, word, 0, NULL, 0) == 0);
        }
        case op_NRE: {
            ssl_expr *e1;
            ssl_expr *e2;
            char *word;
            regex_t *regex;

            e1 = (ssl_expr *)node->node_arg1;
            e2 = (ssl_expr *)node->node_arg2;
            word = ssl_expr_eval_word(r, e1);
            regex = (regex_t *)(e2->node_arg1);
            return !(ap_regexec(regex, word, 0, NULL, 0) == 0);
        }
        default: {
            ssl_expr_error = "Internal evaluation error: Unknown expression node";
            return FALSE;
        }
    }
}