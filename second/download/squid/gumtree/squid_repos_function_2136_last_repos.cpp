static ssize_t
htcpBuildSpecifier(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t s;
    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.method, (stuff->S.method?strlen(stuff->S.method):0));

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.uri, (stuff->S.uri?strlen(stuff->S.uri):0));

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.version, (stuff->S.version?strlen(stuff->S.version):0));

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->S.req_hdrs, stuff->S.reqHdrsSz);

    if (s < 0)
        return s;

    off += s;

    debugs(31, 3, "htcpBuildSpecifier: size " << off);

    return off;
}