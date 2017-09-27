E(void) ap_log_cerror_(const char *file, int line, int module_index,
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