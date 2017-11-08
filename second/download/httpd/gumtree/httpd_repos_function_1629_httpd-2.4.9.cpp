static const char *wd_cmd_watchdog_int(cmd_parms *cmd, void *dummy,
                                       const char *arg)
{
    int i;
    const char *errs = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (errs != NULL)
        return errs;
    if (wd_interval_set)
       return "Duplicate WatchdogInterval directives are not allowed";
    if ((i = atoi(arg)) < 1)
        return "Invalid WatchdogInterval value";

    wd_interval = apr_time_from_sec(i);
    wd_interval_set = 1;
    return NULL;
}