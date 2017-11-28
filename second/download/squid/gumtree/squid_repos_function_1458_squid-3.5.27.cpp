SBuf&
SBuf::trim(const SBuf &toRemove, bool atBeginning, bool atEnd)
{
    ++stats.trim;
    if (atEnd) {
        const char *p = bufEnd()-1;
        while (!isEmpty() && memchr(toRemove.buf(), *p, toRemove.length()) != NULL) {
            //current end-of-buf is in the searched set
            --len_;
            --p;
        }
    }
    if (atBeginning) {
        const char *p = buf();
        while (!isEmpty() && memchr(toRemove.buf(), *p, toRemove.length()) != NULL) {
            --len_;
            ++off_;
            ++p;
        }
    }
    if (isEmpty())
        clear();
    return *this;
}