static const char *set_threads_to_start(cmd_parms *cmd, void *dummy, const char *arg) 
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_to_start = atoi(arg);
    if (ap_threads_to_start < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "StartThreads set to a value less than 0, reset to 1");
        ap_threads_to_start = 1;
    }
    return NULL;
}