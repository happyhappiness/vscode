void ssl_log_xerror(const char *file, int line, int level, apr_status_t rv,
                    apr_pool_t *ptemp, server_rec *s, X509 *cert,
                    const char *fmt, ...)
{
    if (APLOG_IS_LEVEL(s,level)) {
       va_list ap;
       va_start(ap, fmt);
       ssl_log_cert_error(file, line, level, rv, s, NULL, NULL, ptemp,
                          cert, fmt, ap);
       va_end(ap);
    }
}