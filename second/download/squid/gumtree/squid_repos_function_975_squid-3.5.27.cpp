unsigned short
GetShort(void)
{
    char *token = ConfigParser::NextToken();

    if (token == NULL)
        self_destruct();

    return xatos(token);
}