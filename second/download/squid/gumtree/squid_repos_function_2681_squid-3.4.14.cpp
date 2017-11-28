static ssize_t
htcpBuildSpecifier(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t s;
    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.method);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.uri);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.version);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.req_hdrs);

    if (s < 0)
        return s;

    off += s;

    debugs(31, 3, "htcpBuildSpecifier: size " << off);

    return off;
}