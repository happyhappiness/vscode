static void log_info(const char *format, ...)
{
    va_list args;

    va_start (args, format);
    vlog("INFO", format, args);
    va_end (args);
}