void
FtpStateData::printfReplyBody(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    static char buf[4096];
    buf[0] = '\0';
    vsnprintf(buf, 4096, fmt, args);
    writeReplyBody(buf, strlen(buf));
    va_end(args);
}