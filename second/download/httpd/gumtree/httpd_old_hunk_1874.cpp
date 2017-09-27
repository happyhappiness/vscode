        /* Set up the listeners */
        get_listeners_from_parent(s);

        /* Done reading from the parent, close that channel */
        CloseHandle(pipe);

        ap_my_generation = ap_scoreboard_image->global->running_generation;
    }
    else {
        /* Single process mode - this lock doesn't even need to exist */
        rv = apr_proc_mutex_create(&start_mutex, signal_name_prefix,
                                   APR_LOCK_DEFAULT, s->process->pool);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                         "%s child %lu: Unable to init the start_mutex.",
                         service_name, my_pid);
            exit(APEXIT_CHILDINIT);
        }

        /* Borrow the shutdown_even as our _child_ loop exit event */
        exit_event = shutdown_event;
    }
}


AP_DECLARE(int) ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    static int restart = 0;            /* Default is "not a restart" */

    if (!restart) {
        first_thread_limit = thread_limit;
    }

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
                     "Child %lu: Child process is running", my_pid);

        child_main(pconf);

        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %lu: Child process is exiting", my_pid);
        return 1;
    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "%s configured -- resuming normal operations",
                     ap_get_server_description());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "Server built: %s", ap_get_server_built());

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)
        {
            /* Shutting down. Clean up... */
