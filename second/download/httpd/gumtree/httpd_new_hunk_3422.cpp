    }

    if ((parent_pid != my_pid) || one_process)
    {
        /* The child process or in one_process (debug) mode
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00453)
                     "Child process is running");

        child_main(pconf);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00454)
                     "Child process is exiting");
        return DONE;
    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00455)
                     "%s configured -- resuming normal operations",
                     ap_get_server_description());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00456)
                     "Server built: %s", ap_get_server_built());
        ap_log_command_line(plog, s);

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)
        {
            /* Shutting down. Clean up... */
            ap_remove_pid(pconf, ap_pid_fname);
            apr_proc_mutex_destroy(start_mutex);

            CloseHandle(restart_event);
            CloseHandle(shutdown_event);

            return DONE;
