void appendf(const char *fmt,...) PRINTF_FORMAT_ARG2
    {
        va_list args;
        va_start(args, fmt);
        vappendf(fmt, args);
        va_end(args);
    }