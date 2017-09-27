E(void) ap_log_error_(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const server_rec *s, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, module_index, level, status, s, NULL, NULL,
                   NULL, fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_perror_(const char *file, int line, int module_index,
                                int level, apr_status_t status, apr_pool_t *p,
                                const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, module_index, level, status, NULL, NULL, NULL,
                   p, fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_rerror_(const char *file, int line, int module_index,
                                int level, apr_status_t status,
                                const request_rec *r, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, module_index, level, status, r->server, NULL, r,
                   NULL, fmt, args);;