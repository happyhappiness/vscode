bool
httpHeaderParseOffset(const char *start, int64_t *value, char **endPtr)
{
    char *end = nullptr;
    errno = 0;
    const int64_t res = strtoll(start, &end, 10);
    if (errno && !res) {
        debugs(66, 7, "failed to parse malformed offset in " << start);
        return false;
    }
    if (errno == ERANGE && (res == LLONG_MIN || res == LLONG_MAX)) { // no overflow
        debugs(66, 7, "failed to parse huge offset in " << start);
        return false;
    }
    if (start == end) {
        debugs(66, 7, "failed to parse empty offset");
        return false;
    }
    *value = res;
    if (endPtr)
        *endPtr = end;
    debugs(66, 7, "offset " << start << " parsed as " << res);
    return true;
}