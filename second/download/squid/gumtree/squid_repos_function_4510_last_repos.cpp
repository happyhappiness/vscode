bool
Store::Disk::optionReadOnlyParse(char const *option, const char *value, int)
{
    if (strcmp(option, "no-store") != 0 && strcmp(option, "read-only") != 0)
        return false;

    if (strcmp(option, "read-only") == 0) {
        debugs(3, DBG_PARSE_NOTE(3), "UPGRADE WARNING: Replace cache_dir option 'read-only' with 'no-store'.");
    }

    bool read_only = 0;

    if (value)
        read_only = (xatoi(value) != 0);
    else
        read_only = true;

    flags.read_only = read_only;

    return true;
}