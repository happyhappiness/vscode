int64_t
GetInteger64(void)
{
    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return -1; // not reachable
    }

    return xatoll(token, 10);
}