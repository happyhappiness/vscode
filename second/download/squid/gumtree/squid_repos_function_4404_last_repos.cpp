static int
wccmparray(const wchar_t * str, const wchar_t ** array)
{
    while (*array) {
        debug("Windows group: %S, Squid group: %S\n", str, *array);
        if (wcscmp(str, *array) == 0)
            return 0;
        ++array;
    }
    return -1;
}