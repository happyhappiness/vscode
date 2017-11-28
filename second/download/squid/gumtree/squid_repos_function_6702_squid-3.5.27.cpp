static std::ostream &
operator <<(std::ostream &os, const stackmember &s)
{
    switch (s.valuetype) {

    case ESI_EXPR_INVALID:
        os << " Invalid ";
        break;

    case ESI_EXPR_LITERAL:
        printLiteral(os, s);
        break;

    case ESI_EXPR_EXPR:
        os << (s.value.integral ? "true" : "false");
        break;

    case ESI_EXPR_OR:
        os << "|";
        break;

    case ESI_EXPR_AND:
        os << "&";
        break;

    case ESI_EXPR_NOT:
        os << "!";
        break;

    case ESI_EXPR_START:
        os << "(";
        break;

    case ESI_EXPR_END:
        os << ")";
        break;

    case ESI_EXPR_EQ:
        os << "==";
        break;

    case ESI_EXPR_NOTEQ:
        os << "!=";
        break;

    case ESI_EXPR_LESS:
        os << "<";
        break;

    case ESI_EXPR_LESSEQ:
        os << "<=";
        break;

    case ESI_EXPR_MORE:
        os << ">";
        break;

    case ESI_EXPR_MOREEQ:
        os << ">=";
        break;
    }

    return os;
}