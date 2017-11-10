static int ap_expr_eval_comp(ap_expr_eval_ctx_t *ctx, const ap_expr_t *node)
{
    const ap_expr_t *e1 = node->node_arg1;
    const ap_expr_t *e2 = node->node_arg2;
    switch (node->node_op) {
    case op_EQ:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) == 0);
    case op_NE:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) != 0);
    case op_LT:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <  0);
    case op_LE:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <= 0);
    case op_GT:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >  0);
    case op_GE:
        return (intstrcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >= 0);
    case op_STR_EQ:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) == 0);
    case op_STR_NE:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) != 0);
    case op_STR_LT:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <  0);
    case op_STR_LE:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) <= 0);
    case op_STR_GT:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >  0);
    case op_STR_GE:
        return (strcmp(ap_expr_eval_word(ctx, e1), ap_expr_eval_word(ctx, e2)) >= 0);
    case op_IN: {
            const char *needle = ap_expr_eval_word(ctx, e1);
            if (e2->node_op == op_ListElement) {
                do {
                    const ap_expr_t *val = e2->node_arg1;
                    AP_DEBUG_ASSERT(e2->node_op == op_ListElement);
                    if (strcmp(needle, ap_expr_eval_word(ctx, val)) == 0) {
                        return 1;
                        break;
                    }
                    e2 = e2->node_arg2;
                } while (e2 != NULL);
            }
            else if (e2->node_op == op_ListFuncCall) {
                const ap_expr_t *info = e2->node_arg1;
                const ap_expr_t *arg = e2->node_arg2;
                ap_expr_list_func_t *func = (ap_expr_list_func_t *)info->node_arg1;
                apr_array_header_t *haystack;
                int i = 0;
                AP_DEBUG_ASSERT(func != NULL);
                AP_DEBUG_ASSERT(info->node_op == op_ListFuncInfo);
                haystack = (*func)(ctx, info->node_arg2, ap_expr_eval_word(ctx, arg));
                if (haystack == NULL)
                    return 0;
                for (; i < haystack->nelts; i++) {
                    if (strcmp(needle, APR_ARRAY_IDX(haystack,i,char *)) == 0)
                        return 1;
                }
            }
            return 0;
        }
    case op_REG:
    case op_NRE: {
            const char *word = ap_expr_eval_word(ctx, e1);
            const ap_regex_t *regex = e2->node_arg1;
            int result;

            /*
             * $0 ... $9 may contain stuff the user wants to keep. Therefore
             * we only set them if there are capturing parens in the regex.
             */
            if (regex->re_nsub > 0) {
                result = (0 == ap_regexec(regex, word, ctx->re_nmatch,
                                          ctx->re_pmatch, 0));
                *ctx->re_source = result ? word : NULL;
            }
            else {
                result = (0 == ap_regexec(regex, word, 0, NULL, 0));
            }

            if (node->node_op == op_REG)
                return result;
            else
                return !result;
        }
    default:
        *ctx->err = "Internal evaluation error: Unknown comp expression node";
        return -1;
    }
}