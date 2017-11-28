void
printmember (stackmember s)
{
    switch (s.valuetype) {

    case ESI_EXPR_INVALID:
        debug (86,1) (" Invalid ");
        break;

    case ESI_EXPR_LITERAL:
        printliteral (s);
        break;

    case ESI_EXPR_EXPR:
        debug (86,1) ("%s", s.value.integral ? "true" : "false");
        break;

    case ESI_EXPR_OR:
        debug (86,1) ("|");
        break;

    case ESI_EXPR_AND:
        debug (86,1) ("&");
        break;

    case ESI_EXPR_NOT:
        debug (86,1) ("!");
        break;

    case ESI_EXPR_START:
        debug (86,1) ("(");
        break;

    case ESI_EXPR_END:
        debug (86,1) (")");
        break;

    case ESI_EXPR_EQ:
        debug (86,1) ("==");
        break;

    case ESI_EXPR_NOTEQ:
        debug (86,1) ("!=");
        break;

    case ESI_EXPR_LESS:
        debug (86,1) ("<");
        break;

    case ESI_EXPR_LESSEQ:
        debug (86,1) ("<=");
        break;

    case ESI_EXPR_MORE:
        debug (86,1) (">");
        break;

    case ESI_EXPR_MOREEQ:
        debug (86,1) (">=");
        break;
    }
}