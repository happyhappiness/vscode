void ssl_log_cxerror(const char *file, int line, int level, apr_status_t rv,
                     conn_rec *c, X509 *cert, const char *fmt, ...)
{
    if (APLOG_IS_LEVEL(mySrvFromConn(c),level)) {
       va_list ap;
       va_start(ap, fmt);
       ssl_log_cert_error(file, line, level, rv, NULL, c, NULL, c->pool,
                          cert, fmt, ap);
       va_end(ap);
    }
}