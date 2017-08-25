int ZEXPORTVA gzprintf (gzFile file, const char *format, /* args */ ...)
{
    char buf[Z_PRINTF_BUFSIZE];
    va_list va;
    int len;

    va_start(va, format);
#ifdef HAS_vsnprintf
    (void)vsnprintf(buf, sizeof(buf), format, va);
#else
    (void)vsprintf(buf, format, va);
#endif
    va_end(va);
    len = strlen(buf); /* some *sprintf don't return the nb of bytes written */
    if (len <= 0) return 0;

    return gzwrite(file, buf, (unsigned)len);
}