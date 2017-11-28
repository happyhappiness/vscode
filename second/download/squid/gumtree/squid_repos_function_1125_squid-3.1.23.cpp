static void
parse_uri_whitespace(int *var)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcasecmp(token, "strip"))
        *var = URI_WHITESPACE_STRIP;
    else if (!strcasecmp(token, "deny"))
        *var = URI_WHITESPACE_DENY;
    else if (!strcasecmp(token, "allow"))
        *var = URI_WHITESPACE_ALLOW;
    else if (!strcasecmp(token, "encode"))
        *var = URI_WHITESPACE_ENCODE;
    else if (!strcasecmp(token, "chop"))
        *var = URI_WHITESPACE_CHOP;
    else
        self_destruct();
}