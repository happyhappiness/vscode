static void log_debug(const char *format, ...)
{
    va_list args;

    if ( tq_debug_enabled ) {
        va_start (args, format);
        vlog("DEBUG", format, args);
        va_end (args);
    }
}