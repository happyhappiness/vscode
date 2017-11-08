static int winnt_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec* s)
{
    static int restart_num = 0;
    apr_status_t rv = 0;

    /* Handle the following SCM aspects in this phase:
     *
     *   -k install (catch and exit as install was handled in rewrite_args)
     *   -k config  (catch and exit as config was handled in rewrite_args)
     *   -k start
     *   -k restart
     *   -k runservice [Win95, only once - after we parsed the config]
     *
     * because all of these signals are useful _only_ if there
     * is a valid conf\httpd.conf environment to start.
     *
     * We reached this phase by avoiding errors that would cause
     * these options to fail unexpectedly in another process.
     */

    if (!strcasecmp(signal_arg, "install")) {
        /* Service install happens in the rewrite_args hooks. If we
         * made it this far, the server configuration is clean and the
         * service will successfully start.
         */
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit(0);
    }
    if (!strcasecmp(signal_arg, "config")) {
        /* Service reconfiguration happens in the rewrite_args hooks. If we
         * made it this far, the server configuration is clean and the
         * service will successfully start.
         */
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit(0);
    }

    if (!strcasecmp(signal_arg, "start")) {
        ap_listen_rec *lr;

        /* Close the listening sockets. */
        for (lr = ap_listeners; lr; lr = lr->next) {
            apr_socket_close(lr->sd);
            lr->active = 0;
        }
        rv = mpm_service_start(ptemp, inst_argc, inst_argv);
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit (rv);
    }

    if (!strcasecmp(signal_arg, "restart")) {
        mpm_signal_service(ptemp, 1);
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit (rv);
    }

    if (parent_pid == my_pid)
    {
        if (restart_num++ == 1)
        {
            /* This code should be run once in the parent and not run
             * across a restart
             */
            PSECURITY_ATTRIBUTES sa = GetNullACL();  /* returns NULL if invalid (Win95?) */
            setup_signal_names(apr_psprintf(pconf,"ap%lu", parent_pid));

            ap_log_pid(pconf, ap_pid_fname);

            /* Create shutdown event, apPID_shutdown, where PID is the parent
             * Apache process ID. Shutdown is signaled by 'apache -k shutdown'.
             */
            shutdown_event = CreateEvent(sa, FALSE, FALSE, signal_shutdown_name);
            if (!shutdown_event) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Parent: Cannot create shutdown event %s", signal_shutdown_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            /* Create restart event, apPID_restart, where PID is the parent
             * Apache process ID. Restart is signaled by 'apache -k restart'.
             */
            restart_event = CreateEvent(sa, FALSE, FALSE, signal_restart_name);
            if (!restart_event) {
                CloseHandle(shutdown_event);
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Parent: Cannot create restart event %s", signal_restart_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            CleanNullACL((void *)sa);

            /* Now that we are flying at 15000 feet...
             * wipe out the Win95 service console,
             * signal the SCM the WinNT service started, or
             * if not a service, setup console handlers instead.
             */
            if (!strcasecmp(signal_arg, "runservice"))
            {
                if (osver.dwPlatformId != VER_PLATFORM_WIN32_NT)
                {
                    rv = mpm_service_to_start(&service_name,
                                              s->process->pool);
                    if (rv != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                     "%s: Unable to start the service manager.",
                                     service_name);
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }
                }
            }

            /* Create the start mutex, as an unnamed object for security.
             * Ths start mutex is used during a restart to prevent more than
             * one child process from entering the accept loop at once.
             */
            rv =  apr_proc_mutex_create(&start_mutex, NULL,
                                        APR_LOCK_DEFAULT,
                                        ap_server_conf->process->pool);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "%s: Unable to create the start_mutex.",
                             service_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        /* Always reset our console handler to be the first, even on a restart
        *  because some modules (e.g. mod_perl) might have set a console 
        *  handler to terminate the process.
        */
        if (strcasecmp(signal_arg, "runservice"))
            mpm_start_console_handler();
    }
    else /* parent_pid != my_pid */
    {
        mpm_start_child_console_handler();
    }
    return OK;
}