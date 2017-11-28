static void
parse_TokenOrQuotedString(char **var)
{
    safe_free(*var);

    char *token = ConfigParser::NextQuotedToken();
    if (!token) {
        self_destruct();
        return;
    }

    *var = xstrdup(token);
}