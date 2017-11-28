static int
rfc1035LabelPack(char *buf, size_t sz, const char *label)
{
    int off = 0;
    size_t len = label ? strlen(label) : 0;
    if (label)
        assert(!strchr(label, '.'));
    if (len > RFC1035_MAXLABELSZ)
        len = RFC1035_MAXLABELSZ;
    assert(sz >= len + 1);
    *(buf + off) = (char) len;
    off++;
    memcpy(buf + off, label, len);
    off += len;
    return off;
}