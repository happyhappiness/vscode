bool
urlIsRelative(const char *url)
{
    const char *p;

    if (url == NULL) {
        return (false);
    }
    if (*url == '\0') {
        return (false);
    }

    for (p = url; *p != '\0' && *p != ':' && *p != '/'; ++p);

    if (*p == ':') {
        return (false);
    }
    return (true);
}