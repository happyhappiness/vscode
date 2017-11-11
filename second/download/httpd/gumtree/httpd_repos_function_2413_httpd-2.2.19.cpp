static const char *set_max_requests_per_thread (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_max_requests_per_thread = atoi(arg);
    if (ap_max_requests_per_thread < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: MaxRequestsPerThread was set below 0"
                     "reset to 0, but this may not be what you want.");
        ap_max_requests_per_thread = 0;
    }

    return NULL;
}