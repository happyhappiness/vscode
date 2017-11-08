void ssl_log_rxerror(const char *file, int line, int level, apr_status_t rv,
                     request_rec *r, X509 *cert, const char *fmt, ...)
{
    if (APLOG_R_IS_LEVEL(r,level)) {
       va_list ap;
       va_start(ap, fmt);
       ssl_log_cert_error(file, line, level, rv, NULL, NULL, r, r->pool,
                          cert, fmt, ap);
       va_end(ap);
    }
}