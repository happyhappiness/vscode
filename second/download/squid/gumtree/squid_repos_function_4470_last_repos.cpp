void
log(char *format,...)
{
    if (!log_enabled)
        return;
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}