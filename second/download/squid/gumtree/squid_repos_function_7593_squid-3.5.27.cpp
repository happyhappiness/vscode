void
debug(const char *format,...)
{
    if (!debug_enabled)
        return;
    va_list args;
    va_start (args,format);
    vfprintf(stderr,format,args);
    va_end(args);
}