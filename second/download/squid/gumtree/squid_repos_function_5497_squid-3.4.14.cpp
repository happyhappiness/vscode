void
logfilePrintf(Logfile * lf, const char *fmt,...)
{
    va_list args;
    char buf[8192];
    int s;

    va_start(args, fmt);

    s = vsnprintf(buf, 8192, fmt, args);

    if (s > 8192) {
        s = 8192;

        if (fmt[strlen(fmt) - 1] == '\n')
            buf[8191] = '\n';
    }

    logfileWrite(lf, buf, (size_t) s);
    va_end(args);
}