static void
httpHeaderPutStrvf(HttpHeader * hdr, Http::HdrType id, const char *fmt, va_list vargs)
{
    MemBuf mb;
    mb.init();
    mb.vappendf(fmt, vargs);
    hdr->putStr(id, mb.buf);
    mb.clean();
}