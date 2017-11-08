static void log_error_va_glue(const char *file, int line, int module_index,
                              int level, apr_status_t status,
                              const server_rec *s, const conn_rec *c,
                              const request_rec *r, apr_pool_t *pool,
                              const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, module_index, level, status, s, c, r, pool,
                   fmt, args);
    va_end(args);
}