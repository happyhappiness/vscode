void
httpHeaderPutStrf(HttpHeader * hdr, http_hdr_type id, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);

    httpHeaderPutStrvf(hdr, id, fmt, args);
    va_end(args);
}