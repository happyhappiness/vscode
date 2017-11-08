void printerr(char *fmt, ...) 
{
    char str[1024];
    va_list args;
    if (!verbose)
        return;
    va_start(args, fmt);
    wvsprintf(str, fmt, args);
    OutputDebugString(str);
}