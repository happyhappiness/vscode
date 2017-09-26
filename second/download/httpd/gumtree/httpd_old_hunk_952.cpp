    if (changed_limit_at_restart) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_SUCCESS, ap_server_conf,
                     "WARNING: Attempt to change ThreadLimit ignored "
                     "during restart");
        changed_limit_at_restart = 0;
    }
    
    /* ### If non-graceful restarts are ever introduced - we need to rerun 
     * the pre_mpm hook on subsequent non-graceful restarts.  But Win32 
     * has only graceful style restarts - and we need this hook to act 
     * the same on Win32 as on Unix.
     */
    if (!restart && ((parent_pid == my_pid) || one_process)) {
        /* Set up the scoreboard. */
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return 1;
        }
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
        return 1;
    }
    else 
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "%s configured -- resuming normal operations",
                     ap_get_server_version());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "Server built: %s", ap_get_server_built());

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart) 
        {
            /* Shutting down. Clean up... */
            const char *pidfile = ap_server_root_relative (pconf, ap_pid_fname);

            if (pidfile != NULL && unlink(pidfile) == 0) {
                ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
