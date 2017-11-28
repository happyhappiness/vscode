char *
ConfigParser::NextElement(bool *wasQuoted)
{
    if (wasQuoted)
        *wasQuoted = false;

    // Get all of the remaining string
    char *token = strtok(NULL, "");
    if (token == NULL)
        return NULL;

    // skip leading whitespace (may skip the entire token that way)
    while (xisspace(*token)) ++token;

    if (*token != '"')
        return StripComment(strtok(token, w_space));

    if (wasQuoted)
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
        debugs(3, DBG_CRITICAL, "missing '\"' at the end of quoted string" );
        self_destruct();
    }
    strtok(s-1, "\""); /*Reset the strtok to point after the "  */
    *s = '\0';

    return (token+1);
}