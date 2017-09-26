    restart_pending = shutdown_pending = 0;

    event_handles[SHUTDOWN_HANDLE] = shutdown_event;
    event_handles[RESTART_HANDLE] = restart_event;

    /* Create a single child process */
    rv = create_process(pconf, &event_handles[CHILD_HANDLE], 
                        &child_exit_event, &child_pid);
    if (rv < 0) 
    {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "master_main: create child process failed. Exiting.");
        shutdown_pending = 1;
        goto die_now;
    }
