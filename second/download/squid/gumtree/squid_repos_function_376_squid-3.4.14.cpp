static void
debug(char *format,...)
{
    if (debug_enabled) {
        va_list args;

        va_start(args,format);
        fprintf(stderr, "nt_auth[%d]: ",getpid());
        vfprintf(stderr, format, args);
        va_end(args);
    }
}