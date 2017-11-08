static void log_err(const char *fmt,...)
{
#ifdef AP_LOG_EXEC
    va_list ap;

    va_start(ap, fmt);
    err_output(1, fmt, ap); /* 1 == is_error */
    va_end(ap);
#endif /* AP_LOG_EXEC */
    return;
}