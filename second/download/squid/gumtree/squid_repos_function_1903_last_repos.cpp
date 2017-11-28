void
httpHeaderPutStrf(HttpHeader * hdr, Http::HdrType id, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);

    httpHeaderPutStrvf(hdr, id, fmt, args);
    va_end(args);
}