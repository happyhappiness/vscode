static int winnt_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    static int restart = 0;            /* Default is "not a restart" */

    /* ### If non-graceful restarts are ever introduced - we need to rerun
     * the pre_mpm hook on subsequent non-graceful restarts.  But Win32
     * has only graceful style restarts - and we need this hook to act
     * the same on Win32 as on Unix.
     */
    if (!restart && ((parent_pid == my_pid) || one_process)) {
        /* Set up the scoreboard. */
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return DONE;
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
        }
    }

    return OK; /* Restart */
}