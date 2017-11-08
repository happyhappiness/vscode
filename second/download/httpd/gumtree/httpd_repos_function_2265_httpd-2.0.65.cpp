static const char *set_max_spare_threads(cmd_parms *cmd, void *dummy,
                                         const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    max_spare_threads = atoi(arg);
    if (max_spare_threads >= thread_limit) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: detected MinSpareThreads set higher than");
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "ThreadLimit. Resetting to %d", thread_limit);
       max_spare_threads = thread_limit;
    }
    return NULL;
}