    }

    if ((parent_pid != my_pid) || one_process)
    {
        /* The child process or in one_process (debug) mode
         */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is running", my_pid);

        child_main(pconf);

        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is exiting", my_pid);
        return DONE;
    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "%s configured -- resuming normal operations",
                     ap_get_server_description());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "Server built: %s", ap_get_server_built());
        ap_log_command_line(plog, s);

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)
        {
            /* Shutting down. Clean up... */
            const char *pidfile = ap_server_root_relative (pconf, ap_pid_fname);

            if (pidfile != NULL && unlink(pidfile) == 0) {
                ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
                             ap_server_conf, "removed PID file %s (pid=%ld)",
                             pidfile, GetCurrentProcessId());
            }
            apr_proc_mutex_destroy(start_mutex);

            CloseHandle(restart_event);
            CloseHandle(shutdown_event);

            return DONE;
