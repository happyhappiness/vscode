AP_DECLARE(apr_array_header_t *) ap_get_status_table(apr_pool_t *p)
{
    /* NOP */
    return NULL;
}

/* 
 * Command processors 
 */

static const char *set_threads_per_child (cmd_parms *cmd, void *dummy, char *arg) 
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    if (ap_threads_per_child > thread_limit) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                     "value of %d threads,", ap_threads_per_child, 
                     thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     " lowering ThreadsPerChild to %d. To increase, please"
                     " see the", thread_limit);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     " ThreadLimit directive.");
        ap_threads_per_child = thread_limit;
    }
    else if (ap_threads_per_child < 1) {
	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: Require ThreadsPerChild > 0, setting to 1");
	ap_threads_per_child = 1;
    }
    return NULL;
}
static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg) 
{
    int tmp_thread_limit;
    
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    tmp_thread_limit = atoi(arg);
