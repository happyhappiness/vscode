        strcpy(errstr + len, APR_EOL_STR);
        apr_file_puts(errstr, logf);
        apr_file_flush(logf);
    }
#ifdef HAVE_SYSLOG
    else {
        syslog(level_and_mask, "%s", errstr);
    }
#endif

    ap_run_error_log(file, line, level, status, s, r, pool, errstr + errstrlen);
}

AP_DECLARE(void) ap_log_error(const char *file, int line, int level,
                              apr_status_t status, const server_rec *s,
                              const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, status, s, NULL, NULL, NULL, fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_perror(const char *file, int line, int level,
                               apr_status_t status, apr_pool_t *p,
                               const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, status, NULL, NULL, NULL, p, fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_rerror(const char *file, int line, int level,
                               apr_status_t status, const request_rec *r,
                               const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, status, r->server, NULL, r, NULL, fmt,
                   args);

    /*
     * IF APLOG_TOCLIENT is set,
     * AND the error level is 'warning' or more severe,
     * AND there isn't already error text associated with this request,
     * THEN make the message text available to ErrorDocument and
