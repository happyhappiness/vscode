double
xatof(const char *token)
{
    char *end = NULL;
    double ret = strtod(token, &end);

    if (ret == 0 && end == token) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: No digits were found in the input value '" << token << "'.");
        self_destruct();
    }

    if (*end) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid value: '" << token << "' is supposed to be a number.");
        self_destruct();
    }

    return ret;
}