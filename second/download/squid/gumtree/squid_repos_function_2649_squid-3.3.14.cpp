static ssize_t
htcpBuildDetail(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t s;
    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.resp_hdrs);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.entity_hdrs);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.cache_hdrs);

    if (s < 0)
        return s;

    off += s;

    return off;
}