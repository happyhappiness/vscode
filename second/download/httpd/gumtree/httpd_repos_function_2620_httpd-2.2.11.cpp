void abts_log_message(const char *fmt, ...)
{
    va_list args;
    update_status();

    if (verbose) {
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        fflush(stderr);
    }
}