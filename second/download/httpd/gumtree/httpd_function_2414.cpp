static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    int tmp_thread_limit;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    tmp_thread_limit = atoi(arg);
    /* you cannot change ThreadLimit across a restart; ignore
     * any such attempts
     */
    if (first_thread_limit &&
        tmp_thread_limit != thread_limit) {
        /* how do we log a message?  the error log is a bit bucket at this
         * point; we'll just have to set a flag so that ap_mpm_run()
         * logs a warning later
         */
        changed_limit_at_restart = 1;
        return NULL;
    }
    thread_limit = tmp_thread_limit;

    if (thread_limit > MAX_THREAD_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: ThreadLimit of %d exceeds compile time limit "
                    "of %d servers,", thread_limit, MAX_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " lowering ThreadLimit to %d.", MAX_THREAD_LIMIT);
       thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: Require ThreadLimit > 0, setting to 1");
        thread_limit = 1;
    }
    return NULL;
}