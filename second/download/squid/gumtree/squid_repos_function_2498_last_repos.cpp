void
storeAppendVPrintf(StoreEntry * e, const char *fmt, va_list vargs)
{
    e->vappendf(fmt, vargs);
}