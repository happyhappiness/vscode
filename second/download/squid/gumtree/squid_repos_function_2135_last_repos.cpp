static ssize_t
htcpBuildCountstr(char *buf, size_t buflen, const char *s, size_t len)
{
    int off = 0;

    if (buflen - off < 2)
        return -1;

    debugs(31, 3, "htcpBuildCountstr: LENGTH = " << len);

    debugs(31, 3, "htcpBuildCountstr: TEXT = {" << (s ? s : "<NULL>") << "}");

    uint16_t length = htons((uint16_t) len);

    memcpy(buf + off, &length, 2);

    off += 2;

    if (buflen - off < len)
        return -1;

    if (len)
        memcpy(buf + off, s, len);

    off += len;

    return off;
}