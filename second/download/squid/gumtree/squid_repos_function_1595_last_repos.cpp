inline size_t
headersEnd(const char *buf, size_t sz)
{
    bool ignored;
    return headersEnd(buf, sz, ignored);
}