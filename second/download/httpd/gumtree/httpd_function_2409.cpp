static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    int tmp_server_limit;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    tmp_server_limit = atoi(arg);
    /* you cannot change ServerLimit across a restart; ignore
     * any such attempts
     */
    if (first_server_limit &&
        tmp_server_limit != server_limit) {
        /* how do we log a message?  the error log is a bit bucket at this
         * point; we'll just have to set a flag so that ap_mpm_run()
         * logs a warning later
         */
        changed_limit_at_restart = 1;
        return NULL;
    }
    server_limit = tmp_server_limit;

    if (server_limit > MAX_SERVER_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: ServerLimit of %d exceeds compile time limit "
                    "of %d servers,", server_limit, MAX_SERVER_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " lowering ServerLimit to %d.", MAX_SERVER_LIMIT);
       server_limit = MAX_SERVER_LIMIT;
    }
    else if (server_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: Require ServerLimit > 0, setting to 1");
        server_limit = 1;
    }
    return NULL;
}