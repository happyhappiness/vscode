static void
parse_tristate(int *var)
{
    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return;
    }

    if (!strcmp(token, "on")) {
        *var = 1;
    } else if (!strcmp(token, "enable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'enable' is deprecated. Please update to use value 'on'.");
        *var = 1;
    } else if (!strcmp(token, "warn")) {
        *var = -1;
    } else if (!strcmp(token, "off")) {
        *var = 0;
    } else if (!strcmp(token, "disable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'disable' is deprecated. Please update to use value 'off'.");
        *var = 0;
    } else {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid option: Tristate options can only be 'on', 'off', or 'warn'.");
        self_destruct();
    }
}