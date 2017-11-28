static void
_db_print_stderr(const char *format, va_list args)
{
    if (1 < Debug::Level())
        return;

    vfprintf(stderr, format, args);
}