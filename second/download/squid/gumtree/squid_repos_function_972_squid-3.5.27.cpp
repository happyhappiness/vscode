int64_t
GetInteger64(void)
{
    char *token = ConfigParser::NextToken();

    if (token == NULL)
        self_destruct();

    return xatoll(token, 10);
}