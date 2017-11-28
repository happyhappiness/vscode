size_t
BuildPrefixInit()
{
    // XXX: This must be kept in sync with the actual debug.cc location
    const char *ThisFileNameTail = "src/debug.cc";

    const char *file=__FILE__;

    // Disable heuristic if it does not work.
    if (!strstr(file, ThisFileNameTail))
        return 0;

    return strlen(file)-strlen(ThisFileNameTail);
}