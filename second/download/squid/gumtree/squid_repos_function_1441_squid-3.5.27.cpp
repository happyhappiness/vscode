SBuf&
SBuf::vappendf(const char *fmt, va_list vargs)
{
    // with (v)appendf() the fmt or an arg might be a dangerous char*
    const Locker blobKeeper(this, buf());

    Must(fmt != NULL);
    int sz = 0;
    //reserve twice the format-string size, it's a likely heuristic
    size_type requiredSpaceEstimate = strlen(fmt)*2;

    char *space = rawSpace(requiredSpaceEstimate);
#ifdef VA_COPY
    va_list ap;
    VA_COPY(ap, vargs);
    sz = vsnprintf(space, spaceSize(), fmt, ap);
    va_end(ap);
#else
    sz = vsnprintf(space, spaceSize(), fmt, vargs);
#endif

    /* check for possible overflow */
    /* snprintf on Linux returns -1 on output errors, or the size
     * that would have been written if enough space had been available */
    /* vsnprintf is standard in C99 */

    if (sz >= static_cast<int>(spaceSize())) {
        // not enough space on the first go, we now know how much we need
        requiredSpaceEstimate = sz*2; // TODO: tune heuristics
        space = rawSpace(requiredSpaceEstimate);
        sz = vsnprintf(space, spaceSize(), fmt, vargs);
        if (sz < 0) // output error in vsnprintf
            throw TextException("output error in second-go vsnprintf",__FILE__,
                                __LINE__);
    }

    if (sz < 0) // output error in either vsnprintf
        throw TextException("output error in vsnprintf",__FILE__, __LINE__);

    // data was appended, update internal state
    len_ += sz;

    /* C99 specifies that the final '\0' is not counted in vsnprintf's
     * return value. Older compilers/libraries might instead count it */
    /* check whether '\0' was appended and counted */
    static bool snPrintfTerminatorChecked = false;
    static bool snPrintfTerminatorCounted = false;
    if (!snPrintfTerminatorChecked) {
        char testbuf[16];
        snPrintfTerminatorCounted = snprintf(testbuf, sizeof(testbuf),
                                             "%s", "1") == 2;
        snPrintfTerminatorChecked = true;
    }
    if (snPrintfTerminatorCounted) {
        --sz;
        --len_;
    }

    store_->size += sz;
    ++stats.append;

    return *this;
}