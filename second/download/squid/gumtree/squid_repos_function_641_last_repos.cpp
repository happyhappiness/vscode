int64_t
xatoll(const char *token, int base, char eov)
{
    char *end = NULL;
    int64_t ret = strtoll(token, &end, base);

    if (end == token) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: No digits were found in the input value '" << token << "'.");
        self_destruct();
    }

    if (*end != eov) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid value: '" << token << "' is supposed to be a number.");
        self_destruct();
    }

    return ret;
}