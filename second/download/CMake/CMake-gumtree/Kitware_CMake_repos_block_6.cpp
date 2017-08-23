{
    char buf[Z_PRINTF_BUFSIZE];
    int len;

    buf[sizeof(buf) - 1] = 0;
#ifdef NO_snprintf
#  ifdef HAS_sprintf_void
    sprintf(buf, format, a1, a2, a3, a4, a5, a6, a7, a8,
            a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
    for (len = 0; len < sizeof(buf); len++)
        if (buf[len] == 0) break;
#  else
    len = sprintf(buf, format, a1, a2, a3, a4, a5, a6, a7, a8,
                a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
#  endif
#else
#  ifdef HAS_snprintf_void
    snprintf(buf, sizeof(buf), format, a1, a2, a3, a4, a5, a6, a7, a8,
             a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
    len = strlen(buf);
#  else
    len = snprintf(buf, sizeof(buf), format, a1, a2, a3, a4, a5, a6, a7, a8,
                 a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
#  endif
#endif
    if (len <= 0 || len >= sizeof(buf) || buf[sizeof(buf) - 1] != 0)
        return 0;
    return gzwrite(file, buf, len);
}