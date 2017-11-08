static void expr_dump_tree(const ap_expr_t *e, const server_rec *s,
                           int loglevel, int indent)
{
    switch (e->node_op) {
    /* no arg */
    case op_NOP:
    case op_True:
    case op_False:
        {
            char *name;
            switch (e->node_op) {
            CASE_OP(op_NOP);
            CASE_OP(op_True);
            CASE_OP(op_False);
            default:
                ap_assert(0);
            }
            ap_log_error(MARK, "%*s%s", indent, " ", name);
        }
        break;

    /* arg1: string, arg2: expr */
    case op_UnaryOpCall:
    case op_BinaryOpCall:
    case op_BinaryOpArgs:
        {
            char *name;
            switch (e->node_op) {
            CASE_OP(op_BinaryOpCall);
            CASE_OP(op_UnaryOpCall);
            CASE_OP(op_BinaryOpArgs);
            default:
                ap_assert(0);
            }
            DUMP_S_E(name, e->node_arg1, e->node_arg2);
        }
        break;

    /* arg1: expr, arg2: expr */
    case op_Comp:
    case op_Not:
    case op_Or:
    case op_And:
    case op_EQ:
    case op_NE:
    case op_LT:
    case op_LE:
    case op_GT:
    case op_GE:
    case op_STR_EQ:
    case op_STR_NE:
    case op_STR_LT:
    case op_STR_LE:
    case op_STR_GT:
    case op_STR_GE:
    case op_IN:
    case op_REG:
    case op_NRE:
    case op_Concat:
    case op_StringFuncCall:
    case op_ListFuncCall:
    case op_ListElement:
        {
            char *name;
            switch (e->node_op) {
            CASE_OP(op_Comp);
            CASE_OP(op_Not);
            CASE_OP(op_Or);
            CASE_OP(op_And);
            CASE_OP(op_EQ);
            CASE_OP(op_NE);
            CASE_OP(op_LT);
            CASE_OP(op_LE);
            CASE_OP(op_GT);
            CASE_OP(op_GE);
            CASE_OP(op_STR_EQ);
            CASE_OP(op_STR_NE);
            CASE_OP(op_STR_LT);
            CASE_OP(op_STR_LE);
            CASE_OP(op_STR_GT);
            CASE_OP(op_STR_GE);
            CASE_OP(op_IN);
            CASE_OP(op_REG);
            CASE_OP(op_NRE);
            CASE_OP(op_Concat);
            CASE_OP(op_StringFuncCall);
            CASE_OP(op_ListFuncCall);
            CASE_OP(op_ListElement);
            default:
                ap_assert(0);
            }
            DUMP_E_E(name, e->node_arg1, e->node_arg2);
        }
        break;
    /* arg1: string */
    case op_Digit:
    case op_String:
        {
            char *name;
            switch (e->node_op) {
            CASE_OP(op_Digit);
            CASE_OP(op_String);
            default:
                ap_assert(0);
            }
            DUMP_S(name, e->node_arg1);
        }
        break;
    /* arg1: pointer, arg2: pointer */
    case op_Var:
    case op_StringFuncInfo:
    case op_UnaryOpInfo:
    case op_BinaryOpInfo:
    case op_ListFuncInfo:
        {
            char *name;
            switch (e->node_op) {
            CASE_OP(op_Var);
            CASE_OP(op_StringFuncInfo);
            CASE_OP(op_UnaryOpInfo);
            CASE_OP(op_BinaryOpInfo);
            CASE_OP(op_ListFuncInfo);
            default:
                ap_assert(0);
            }
            DUMP_P_P(name, e->node_arg1, e->node_arg2);
        }
        break;
    /* arg1: pointer */
    case op_Regex:
        DUMP_P("op_Regex", e->node_arg1);
        break;
    /* arg1: pointer to int */
    case op_RegexBackref:
        DUMP_IP("op_RegexBackref", e->node_arg1);
        break;
    default:
        ap_log_error(MARK, "%*sERROR: INVALID OP %d", indent, " ", e->node_op);
        break;
    }
}