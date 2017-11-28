int
xatoi(const char *token)
{
    int64_t input = xatoll(token, 10);
    int ret = (int) input;

    if (input != static_cast<int64_t>(ret)) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' is larger than the type 'int'.");
        self_destruct();
    }

    return ret;
}