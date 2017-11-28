static void
_db_print_stderr(const char *format, va_list args)
{
    /* FIXME? */
    // if (opt_debug_stderr < Debug::level)

    if (1 < Debug::level)
        return;

    vfprintf(stderr, format, args);
}