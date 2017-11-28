static char *
read_post_request(void)
{
    char *s;

    if ((s = getenv("REQUEST_METHOD")) == NULL)
        return NULL;

    if (0 != strcasecmp(s, "POST"))
        return NULL;

    if ((s = getenv("CONTENT_LENGTH")) == NULL)
        return NULL;

    if (*s == '-') // negative length content huh?
        return NULL;

    uint64_t len;

    char *endptr = s+ strlen(s);
    if ((len = strtoll(s, &endptr, 10)) <= 0)
        return NULL;

    // limit the input to something reasonable.
    // 4KB should be enough for the GET/POST data length, but may be extended.
    size_t bufLen = (len < 4096 ? len : 4095);
    char *buf = (char *)xmalloc(bufLen + 1);

    size_t readLen = fread(buf, 1, bufLen, stdin);
    if (readLen == 0) {
        xfree(buf);
        return NULL;
    }
    buf[readLen] = '\0';
    len -= readLen;

    // purge the remainder of the request entity
    while (len > 0 && readLen) {
        char temp[65535];
        readLen = fread(temp, 1, 65535, stdin);
        len -= readLen;
    }

    return buf;
}