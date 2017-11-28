static void
parse_uri_whitespace(int *var)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcmp(token, "strip"))
        *var = URI_WHITESPACE_STRIP;
    else if (!strcmp(token, "deny"))
        *var = URI_WHITESPACE_DENY;
    else if (!strcmp(token, "allow"))
        *var = URI_WHITESPACE_ALLOW;
    else if (!strcmp(token, "encode"))
        *var = URI_WHITESPACE_ENCODE;
    else if (!strcmp(token, "chop"))
        *var = URI_WHITESPACE_CHOP;
    else {
        debugs(0, DBG_PARSE_NOTE(2), "ERROR: Invalid option '" << token << "': 'uri_whitespace' accepts 'strip', 'deny', 'allow', 'encode', and 'chop'.");
        self_destruct();
    }
}