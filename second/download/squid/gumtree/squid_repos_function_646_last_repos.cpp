unsigned short
GetShort(void)
{
    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return 0; // not reachable
    }

    return xatos(token);
}