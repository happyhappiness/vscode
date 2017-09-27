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
