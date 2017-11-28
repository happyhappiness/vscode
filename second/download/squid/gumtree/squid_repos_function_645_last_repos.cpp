double
GetPercentage(bool limit)
{
    char *token = ConfigParser::NextToken();

    if (!token) {
        debugs(3, DBG_CRITICAL, "FATAL: A percentage value is missing.");
        self_destruct();
        return 0.0; // not reachable
    }

    //if there is a % in the end of the digits, we remove it and go on.
    char* end = &token[strlen(token)-1];
    if (*end == '%') {
        *end = '\0';
    }

    int p = xatoi(token);

    if (p < 0 || (limit && p > 100)) {
        debugs(3, DBG_CRITICAL, "FATAL: The value '" << token << "' is out of range. A percentage should be within [0, 100].");
        self_destruct();
    }

    return static_cast<double>(p) / 100.0;
}