static int winnt_open_logs(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    /* Initialize shared static objects.
     */
    if (parent_pid != my_pid) {
        return OK;
    }

    /* We cannot initialize our listeners if we are restarting
     * (the parent process already has glomed on to them)
     * nor should we do so for service reconfiguration
     * (since the service may already be running.)
     */
    if (!strcasecmp(signal_arg, "restart")
            || !strcasecmp(signal_arg, "config")) {
        return OK;
    }

    if (ap_setup_listeners(s) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    return OK;
}