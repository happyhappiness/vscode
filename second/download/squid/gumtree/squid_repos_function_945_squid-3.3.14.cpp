unsigned short
xatos(const char *token)
{
    long port = xatol(token);

    if (port < 0) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' cannot be less than 0.");
        self_destruct();
    }

    if (port & ~0xFFFF) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: The value '" << token << "' is larger than the type 'short'.");
        self_destruct();
    }

    return port;
}