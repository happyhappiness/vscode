static int
wcstrcmparray(const wchar_t * str, const char **array)
{
    WCHAR wszGroup[GNLEN + 1];  // Unicode Group

    while (*array) {
        MultiByteToWideChar(CP_ACP, 0, *array,
                            strlen(*array) + 1, wszGroup, sizeof(wszGroup) / sizeof(wszGroup[0]));
        debug("Windows group: %S, Squid group: %S\n", str, wszGroup);
        if ((use_case_insensitive_compare ? _wcsicmp(str, wszGroup) : wcscmp(str, wszGroup)) == 0)
            return 0;
        ++array;
    }
    return -1;
}