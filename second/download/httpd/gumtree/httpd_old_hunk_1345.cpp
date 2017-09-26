    {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "master_main: create child process failed. Exiting.");
        shutdown_pending = 1;
        goto die_now;
    }
    if (!strcasecmp(signal_arg, "runservice")) {
        mpm_service_started();
    }

    /* Update the scoreboard. Note that there is only a single active
     * child at once.
