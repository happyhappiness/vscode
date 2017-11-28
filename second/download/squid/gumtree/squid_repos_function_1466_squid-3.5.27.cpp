int
SBuf::scanf(const char *format, ...)
{
    // with the format or an arg might be a dangerous char*
    // that gets invalidated by c_str()
    const Locker blobKeeper(this, buf());

    va_list arg;
    int rv;
    ++stats.scanf;
    va_start(arg, format);
    rv = vsscanf(c_str(), format, arg);
    va_end(arg);
    return rv;
}