static void
_db_print_stderr(const char *format, va_list args)
{
    if (Debug::log_stderr < Debug::Level())
        return;

    if (debug_log == stderr)
        return;

    vfprintf(stderr, format, args);
}