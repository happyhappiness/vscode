int
GetInteger(void)
{
    char *token = ConfigParser::NextToken();
    int i;

    if (!token) {
        self_destruct();
        return -1; // not reachable
    }

    // The conversion must honor 0 and 0x prefixes, which are important for things like umask
    int64_t ret = xatoll(token, 0);

    i = (int) ret;
    if (ret != static_cast<int64_t>(i)) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' is larger than the type 'int'.");
        self_destruct();
    }

    return i;
}