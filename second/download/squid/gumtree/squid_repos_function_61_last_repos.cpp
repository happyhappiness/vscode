void
MemBuf::vappendf(const char *fmt, va_list vargs)
{
#ifdef VA_COPY
    va_list ap;
#endif

    int sz = 0;
    assert(fmt);
    assert(buf);
    assert(!stolen);    /* not frozen */
    /* assert in Grow should quit first, but we do not want to have a scary infinite loop */

    while (capacity <= max_capacity) {
        mb_size_t free_space = capacity - size;
        /* put as much as we can */

#ifdef VA_COPY
        /* Fix of bug 753r. The value of vargs is undefined
         * after vsnprintf() returns. Make a copy of vargs
         * incase we loop around and call vsnprintf() again.
         */
        VA_COPY(ap,vargs);
        sz = vsnprintf(buf + size, free_space, fmt, ap);
        va_end(ap);
#else /* VA_COPY */

        sz = vsnprintf(buf + size, free_space, fmt, vargs);
#endif /*VA_COPY*/
        /* check for possible overflow */
        /* snprintf on Linuz returns -1 on overflows */
        /* snprintf on FreeBSD returns at least free_space on overflows */

        if (sz < 0 || sz >= free_space)
            grow(capacity + 1);
        else
            break;
    }

    size += sz;
    /* on Linux and FreeBSD, '\0' is not counted in return value */
    /* on XXX it might be counted */
    /* check that '\0' is appended and not counted */

    if (!size || buf[size - 1]) {
        assert(!buf[size]);
    } else {
        --size;
    }
}