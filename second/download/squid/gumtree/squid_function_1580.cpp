void
StoreEntry::vappendf(const char *fmt, va_list vargs)
{
    LOCAL_ARRAY(char, buf, 4096);
    *buf = 0;
    int x;

#ifdef VA_COPY
    va_args ap;
    /* Fix of bug 753r. The value of vargs is undefined
     * after vsnprintf() returns. Make a copy of vargs
     * incase we loop around and call vsnprintf() again.
     */
    VA_COPY(ap,vargs);
    errno = 0;
    if ((x = vsnprintf(buf, sizeof(buf), fmt, ap)) < 0) {
        fatal(xstrerr(errno));
        return;
    }
    va_end(ap);
#else /* VA_COPY */
    errno = 0;
    if ((x = vsnprintf(buf, sizeof(buf), fmt, vargs)) < 0) {
        fatal(xstrerr(errno));
        return;
    }
#endif /*VA_COPY*/

    if (x < static_cast<int>(sizeof(buf))) {
        append(buf, x);
        return;
    }

    // okay, do it the slow way.
    char *buf2 = new char[x+1];
    int y = vsnprintf(buf2, x+1, fmt, vargs);
    assert(y >= 0 && y == x);
    append(buf2, y);
    delete[] buf2;
}