void MemBuf::terminate()
{
    assert(size < capacity);
    *space() = '\0';
}

/**
 * vappendf for other printf()'s to use; calls vsnprintf, extends buf if needed
 */
void
MemBuf::vappendf(const char *fmt, va_list vargs)
{
#ifdef VA_COPY
    va_list ap;
#endif

    int sz = 0;
