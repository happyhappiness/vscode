{
    char buf[Z_PRINTF_BUFSIZE];
    va_list va;
    int len;

    buf[sizeof(buf) - 1] = 0;
    va_start(va, format);
#ifdef NO_vsnprintf
#  ifdef HAS_vsprintf_void
    (void)vsprintf(buf, format, va);
    va_end(va);
    for (len = 0; len < sizeof(buf); len++)
        if (buf[len] == 0) break;
#  else
    len = vsprintf(buf, format, va);
    va_end(va);
#  endif
#else
#  ifdef HAS_vsnprintf_void
    (void)vsnprintf(buf, sizeof(buf), format, va);
    va_end(va);
    len = strlen(buf);
#  else
    len = vsnprintf(buf, sizeof(buf), format, va);
    va_end(va);
#  endif
#endif
    if (len <= 0 || len >= (int)sizeof(buf) || buf[sizeof(buf) - 1] != 0)
        return 0;
    return gzwrite(file, buf, (unsigned)len);
}