                       ap_escape_html(r->pool, apr_pvsprintf(r->pool, fmt,
                                                             args)));
    }
    va_end(args);
}

AP_DECLARE(void) ap_log_cerror_(const char *file, int line, int module_index,
                                int level, apr_status_t status,
                                const conn_rec *c, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, module_index, level, status, c->base_server, c,
                   NULL, NULL, fmt, args);
    va_end(args);
}

AP_DECLARE(void) ap_log_command_line(apr_pool_t *plog, server_rec *s)
{
    int i;
    process_rec *process = s->process;
    char *result;
    int len_needed = 0;
    
    /* Piece together the command line from the pieces
     * in process->argv, with spaces in between.
     */
    for (i = 0; i < process->argc; i++) {
        len_needed += strlen(process->argv[i]) + 1;
    }

    result = (char *) apr_palloc(plog, len_needed);
    *result = '\0';

    for (i = 0; i < process->argc; i++) {
        strcat(result, process->argv[i]);
        if ((i+1)< process->argc) {
            strcat(result, " ");
        }
    }
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                 "Command line: '%s'", result);
}

AP_DECLARE(void) ap_log_pid(apr_pool_t *p, const char *filename)
{
    apr_file_t *pid_file = NULL;
    apr_finfo_t finfo;
    static pid_t saved_pid = -1;
    pid_t mypid;
