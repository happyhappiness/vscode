SBuf&
SBuf::appendf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vappendf(fmt, args);
    va_end(args);
    return *this;
}