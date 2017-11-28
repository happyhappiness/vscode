static const char*
FindStatement(const char* line, const char* statement)
{
    assert(line != NULL);
    assert(statement != NULL);

    const char* str = skip_ws(line);
    unsigned len = strlen(statement);
    if (strncmp(str, statement, len) == 0) {
        str += len;
        if (*str == '\0')
            return str;
        else if (xisspace(*str))
            return skip_ws(str);
    }

    return NULL;
}