void MemBuf::consumeWhitespacePrefix()
{
    PROF_start(MemBuf_consumeWhitespace);
    if (contentSize() > 0) {
        const char *end = buf + contentSize();
        const char *p = buf;
        for (; p<end && xisspace(*p); ++p);
        if (p-buf > 0)
            consume(p-buf);
    }
    PROF_stop(MemBuf_consumeWhitespace);
}