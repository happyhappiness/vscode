bool
SwapDir::optionReadOnlyParse(char const *option, const char *value, int isaReconfig)
{
    if (strcmp(option, "no-store") != 0 && strcmp(option, "read-only") != 0)
        return false;

    int read_only = 0;

    if (value)
        read_only = xatoi(value);
    else
        read_only = 1;

    flags.read_only = read_only;

    return true;
}