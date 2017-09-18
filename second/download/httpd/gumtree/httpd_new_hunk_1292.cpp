                       ap_escape_html(r->pool, apr_pvsprintf(r->pool, fmt,
                                                             args)));
    }
    va_end(args);
}

AP_DECLARE(void) ap_log_cerror(const char *file, int line, int level,
                               apr_status_t status, const conn_rec *c,
                               const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, status, c->base_server, c, NULL, NULL,
                   fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_pid(apr_pool_t *p, const char *filename)
{
    apr_file_t *pid_file = NULL;
    apr_finfo_t finfo;
    static pid_t saved_pid = -1;
    pid_t mypid;
