static void
parse_string(char **var)
{
    char *token = ConfigParser::NextToken();
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    *var = xstrdup(token);
}