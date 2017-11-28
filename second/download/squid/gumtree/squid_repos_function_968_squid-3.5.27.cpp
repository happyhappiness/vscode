unsigned int
xatoui(const char *token, char eov)
{
    int64_t input = xatoll(token, 10, eov);
    if (input < 0) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The input value '" << token << "' cannot be less than 0.");
        self_destruct();
    }

    unsigned int ret = (unsigned int) input;
    if (input != static_cast<int64_t>(ret)) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' is larger than the type 'unsigned int'.");
        self_destruct();
    }

    return ret;
}