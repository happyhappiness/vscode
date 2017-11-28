SBuf&
SBuf::Printf(const char *fmt, ...)
{
    // with printf() the fmt or an arg might be a dangerous char*
    // NP: cant rely on vappendf() Locker because of clear()
    const Locker blobKeeper(this, buf());

    va_list args;
    va_start(args, fmt);
    clear();
    vappendf(fmt, args);
    va_end(args);
    return *this;
}