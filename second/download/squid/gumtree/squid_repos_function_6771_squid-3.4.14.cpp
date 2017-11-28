static int
rfc1035NamePack(char *buf, size_t sz, const char *name)
{
    unsigned int off = 0;
    char *copy = xstrdup(name);
    char *t;
    /*
     * NOTE: use of strtok here makes names like foo....com valid.
     */
    for (t = strtok(copy, "."); t; t = strtok(NULL, "."))
        off += rfc1035LabelPack(buf + off, sz - off, t);
    xfree(copy);
    off += rfc1035LabelPack(buf + off, sz - off, NULL);
    assert(off <= sz);
    return off;
}