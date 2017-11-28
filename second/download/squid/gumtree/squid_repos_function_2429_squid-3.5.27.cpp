int
httpHeaderParseInt(const char *start, int *value)
{
    assert(value);
    *value = atoi(start);

    if (!*value && !xisdigit(*start)) {
        debugs(66, 2, "failed to parse an int header field near '" << start << "'");
        return 0;
    }

    return 1;
}