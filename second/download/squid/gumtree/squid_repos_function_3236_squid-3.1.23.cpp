static void
memBufVPrintf(MemBuf * mb, const char *fmt, va_list vargs)
{
    mb->vPrintf(fmt, vargs);
}