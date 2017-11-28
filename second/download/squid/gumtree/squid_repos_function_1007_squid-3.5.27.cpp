void
DelaySpec::parse()
{
    // get the token.
    char *token = ConfigParser::NextToken();
    if (token == NULL)
        self_destruct();

    // no-limit value
    if (strcmp(token, "none") == 0 || token[0] == '-') {
        restore_bps = -1;
        max_bytes = -1;
        return;
    }

    // parse the first digits into restore_bps
    const char *p = NULL;
    if (!StringToInt(token, restore_bps, &p, 10) || *p != '/') {
        debugs(77, DBG_CRITICAL, "ERROR: invalid delay rate '" << token << "'. Expecting restore/max or 'none'.");
        self_destruct();
    }
    p++; // increment past the '/'

    // parse the rest into max_bytes
    if (!StringToInt64(p, max_bytes, NULL, 10)) {
        debugs(77, DBG_CRITICAL, "ERROR: restore rate in '" << token << "' is not a number.");
        self_destruct();
    }
}