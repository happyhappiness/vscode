static void
parse_string(char **var)
{
    safe_free(*var);

    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return;
    }

    *var = xstrdup(token);
}