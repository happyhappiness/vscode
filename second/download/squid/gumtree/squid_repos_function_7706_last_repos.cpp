extern void
snmplib_debug(int lvl, const char *fmt,...)
{
    char buf[BUFSIZ];
    va_list args;
    va_start(args, fmt);

    if (snmplib_debug_hook != NULL) {
        vsnprintf(buf, BUFSIZ, fmt, args);
        snmplib_debug_hook(lvl, buf);
    } else {
        vfprintf(stderr, fmt, args);
    }
    va_end(args);
}