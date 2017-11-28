static void
httpHeaderPutStrvf(HttpHeader * hdr, http_hdr_type id, const char *fmt, va_list vargs)
{
    MemBuf mb;
    mb.init();
    mb.vPrintf(fmt, vargs);
    hdr->putStr(id, mb.buf);
    mb.clean();
}