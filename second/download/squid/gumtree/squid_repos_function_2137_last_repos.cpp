static ssize_t
htcpBuildDetail(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t s;
    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.resp_hdrs, stuff->D.respHdrsSz);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.entity_hdrs, stuff->D.entityHdrsSz);

    if (s < 0)
        return s;

    off += s;

    s = htcpBuildCountstr(buf + off, buflen - off, stuff->D.cache_hdrs, stuff->D.cacheHdrsSz);

    if (s < 0)
        return s;

    off += s;

    return off;
}