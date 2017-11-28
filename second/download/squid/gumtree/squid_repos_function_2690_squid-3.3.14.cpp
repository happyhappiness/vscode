void
ConfigParser::ParseQuotedString(String *var, bool *wasQuoted)
{
    // Get all of the remaining string
    char *token = strtok(NULL, "");
    if (token == NULL)
        self_destruct();

    if (*token != '"') {
        token = strtok(token, w_space);
        var->reset(token);
        if (wasQuoted)
            *wasQuoted = false;
        return;
    } else if (wasQuoted)
        *wasQuoted = true;

    char  *s = token + 1;
    /* scan until the end of the quoted string, unescaping " and \  */
    while (*s && *s != '"') {
        if (*s == '\\') {
            const char * next = s+1; // may point to 0
            memmove(s, next, strlen(next) + 1);
        }
        ++s;
    }

    if (*s != '"') {
        debugs(3, DBG_CRITICAL, "ParseQuotedString: missing '\"' at the end of quoted string" );
        self_destruct();
    }
    strtok(s-1, "\""); /*Reset the strtok to point after the "  */
    *s = '\0';

    var->reset(token+1);
}