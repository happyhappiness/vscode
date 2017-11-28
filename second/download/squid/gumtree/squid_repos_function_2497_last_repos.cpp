void
storeAppendPrintf(StoreEntry * e, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);
    e->vappendf(fmt, args);
    va_end(args);
}