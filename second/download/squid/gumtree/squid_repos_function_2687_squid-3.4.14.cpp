static ssize_t
htcpBuildPacket(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t s;
    ssize_t off = 0;
    size_t hdr_sz = sizeof(htcpHeader);
    htcpHeader hdr;
    /* skip the header -- we don't know the overall length */

    if (buflen < hdr_sz) {
        return 0;
    }

    off += hdr_sz;
    s = htcpBuildData(buf + off, buflen - off, stuff);

    if (s < 0) {
        return 0;
    }

    off += s;
    s = htcpBuildAuth(buf + off, buflen - off);

    if (s < 0) {
        return 0;
    }

    off += s;
    hdr.length = htons((uint16_t) off);
    hdr.major = 0;

    if (old_squid_format)
        hdr.minor = 0;
    else
        hdr.minor = 1;

    memcpy(buf, &hdr, hdr_sz);

    debugs(31, 3, "htcpBuildPacket: size " << off);

    return off;
}