void
parse_onoff(int *var)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcasecmp(token, "on")) {
        *var = 1;
    } else if (!strcasecmp(token, "enable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'enable' is deprecated. Please update to use 'on'.");
        *var = 1;
    } else if (!strcasecmp(token, "off")) {
        *var = 0;
    } else if (!strcasecmp(token, "disable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'disable' is deprecated. Please update to use 'off'.");
        *var = 0;
    } else {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid option: Boolean options can only be 'on' or 'off'.");
        self_destruct();
    }
}