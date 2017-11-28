static void
parse_TokenOrQuotedString(char **var)
{
    char *token = ConfigParser::NextQuotedToken();
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    *var = xstrdup(token);
}