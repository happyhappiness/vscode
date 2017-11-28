void
printmember(stackmember s)
{
    switch (s.valuetype) {

    case ESI_EXPR_INVALID:
        old_debug(86,1)(" Invalid ");
        break;

    case ESI_EXPR_LITERAL:
        printliteral(s);
        break;

    case ESI_EXPR_EXPR:
        old_debug(86,1)("%s", s.value.integral ? "true" : "false");
        break;

    case ESI_EXPR_OR:
        old_debug(86,1)("|");
        break;

    case ESI_EXPR_AND:
        old_debug(86,1)("&");
        break;

    case ESI_EXPR_NOT:
        old_debug(86,1)("!");
        break;

    case ESI_EXPR_START:
        old_debug(86,1)("(");
        break;

    case ESI_EXPR_END:
        old_debug(86,1)(")");
        break;

    case ESI_EXPR_EQ:
        old_debug(86,1)("==");
        break;

    case ESI_EXPR_NOTEQ:
        old_debug(86,1)("!=");
        break;

    case ESI_EXPR_LESS:
        old_debug(86,1)("<");
        break;

    case ESI_EXPR_LESSEQ:
        old_debug(86,1)("<=");
        break;

    case ESI_EXPR_MORE:
        old_debug(86,1)(">");
        break;

    case ESI_EXPR_MOREEQ:
        old_debug(86,1)(">=");
        break;
    }
}