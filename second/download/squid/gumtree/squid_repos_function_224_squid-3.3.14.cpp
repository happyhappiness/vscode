static void log_error(const char *format, ...)
{
    va_list args;

    va_start (args, format);
    vlog("ERROR", format, args);
    va_end (args);
}