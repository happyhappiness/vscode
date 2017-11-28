void
fatalf(const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);
    fatalvf(fmt, args);
    va_end(args);
}