static void log_err(const char *fmt,...)
{
#ifdef AP_LOG_EXEC
    va_list ap;

    va_start(ap, fmt);
    err_output(fmt, ap);
    va_end(ap);
#endif /* AP_LOG_EXEC */
    return;
}