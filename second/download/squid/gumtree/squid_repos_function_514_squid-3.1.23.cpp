static void
print_error(const char *string, const char *token, int type)
{
    assert(string != NULL);
    if (type == ENDOFFILE)
        snmplib_debug(0, "%s(EOF): On or around line %d\n", string, Line);
    else if (token)
        snmplib_debug(0, "%s(%s): On or around line %d\n", string, token, Line);
    else
        snmplib_debug(0, "%s: On or around line %d\n", string, Line);
}