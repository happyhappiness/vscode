int
httpHeaderParseOffset(const char *start, int64_t * value)
{
    errno = 0;
    int64_t res = strtoll(start, NULL, 10);
    if (!res && EINVAL == errno)    /* maybe not portable? */
        return 0;
    *value = res;
    return 1;
}