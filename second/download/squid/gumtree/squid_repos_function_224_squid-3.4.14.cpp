static void log_fatal(const char *format, ...)
{
    va_list args;

    va_start (args, format);
    vlog("FATAL", format, args);
    va_end (args);
}