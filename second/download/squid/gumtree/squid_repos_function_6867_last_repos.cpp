static void
printLiteral(std::ostream &os, const stackmember &s)
{
    switch (s.valuestored) {

    case ESI_LITERAL_INVALID:
        os << " Invalid ";
        break;

    case ESI_LITERAL_FLOAT:
        os << s.value.floating;
        break;

    case ESI_LITERAL_STRING:
        os << '\'' << s.value.string << '\'';
        break;

    case ESI_LITERAL_INT:
        os << s.value.integral;
        break;

    case ESI_LITERAL_BOOL:
        os << (s.value.integral ? "true" : "false");
    }
}