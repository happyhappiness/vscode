void
printliteral (stackmember s)
{
    switch (s.valuestored) {

    case ESI_LITERAL_INVALID:
        debug(86, 1) ( " Invalid " );
        break;

    case ESI_LITERAL_FLOAT:
        debug (86,1) ("%f", s.value.floating);
        break;

    case ESI_LITERAL_STRING:
        debug (86,1) ("'%s'", s.value.string);
        break;

    case ESI_LITERAL_INT:
        debug (86,1) ("%d", s.value.integral);
        break;

    case ESI_LITERAL_BOOL:
        debug (86,1)("%s",s.value.integral ? "true" : "false");
    }
}