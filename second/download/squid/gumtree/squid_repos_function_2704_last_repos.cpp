void
ShmWriter::vappendf(const char *fmt, va_list ap)
{
    SBuf vaBuf;
#if defined(VA_COPY)
    va_list apCopy;
    VA_COPY(apCopy, ap);
    vaBuf.vappendf(fmt, apCopy);
    va_end(apCopy);
#else
    vaBuf.vappendf(fmt, ap);
#endif
    append(vaBuf.rawContent(), vaBuf.length());
}