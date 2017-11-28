static void
debug(char *format,...)
{
#ifdef DEBUG
#ifdef _SQUID_MSWIN_
#if FAIL_DEBUG
    if (debug_enabled || fail_debug_enabled) {
#else
if (debug_enabled) {
#endif
        va_list args;

        va_start(args, format);
        fprintf(stderr, "ntlm-auth[%ld]: ", (long)getpid());
        vfprintf(stderr, format, args);
        va_end(args);
#if FAIL_DEBUG
        fail_debug_enabled = 0;
#endif
    }
#endif /* _SQUID_MSWIN_ */
#endif /* DEBUG */
}