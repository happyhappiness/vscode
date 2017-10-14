static int master_main(server_rec *s, HANDLE shutdown_event, HANDLE restart_event)
{
    int rv, cld;
    int restart_pending;
    int shutdown_pending;
    HANDLE child_exit_event;
    HANDLE event_handles[NUM_WAIT_HANDLES];
    DWORD child_pid;

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
    if (!strcasecmp(signal_arg, "runservice")) {
        mpm_service_started();
    }

    /* Update the scoreboard. Note that there is only a single active
     * child at once.
     */
    ap_scoreboard_image->parent[0].quiescing = 0;
    ap_scoreboard_image->parent[0].pid = child_pid;

    /* Wait for shutdown or restart events or for child death */
    winnt_mpm_state = AP_MPMQ_RUNNING;
    rv = WaitForMultipleObjects(NUM_WAIT_HANDLES, (HANDLE *) event_handles, FALSE, INFINITE);
    cld = rv - WAIT_OBJECT_0;
    if (rv == WAIT_FAILED) {
        /* Something serious is wrong */
        ap_log_error(APLOG_MARK,APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "master_main: WaitForMultipeObjects WAIT_FAILED -- doing server shutdown");
        shutdown_pending = 1;
    }
    else if (rv == WAIT_TIMEOUT) {
        /* Hey, this cannot happen */
        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                     "master_main: WaitForMultipeObjects with INFINITE wait exited with WAIT_TIMEOUT");
        shutdown_pending = 1;
    }
    else if (cld == SHUTDOWN_HANDLE) {
        /* shutdown_event signalled */
        shutdown_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, s,
                     "Parent: Received shutdown signal -- Shutting down the server.");
        if (ResetEvent(shutdown_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "ResetEvent(shutdown_event)");
        }
    }
    else if (cld == RESTART_HANDLE) {
        /* Received a restart event. Prepare the restart_event to be reused
         * then signal the child process to exit.
         */
        restart_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                     "Parent: Received restart signal -- Restarting the server.");
        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s,
                         "Parent: SetEvent for child process %d failed.",
                         event_handles[CHILD_HANDLE]);
        }
        /* Don't wait to verify that the child process really exits,
         * just move on with the restart.
         */
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }
    else {
        /* The child process exited prematurely due to a fatal error. */
        DWORD exitcode;
        if (!GetExitCodeProcess(event_handles[CHILD_HANDLE], &exitcode)) {
            /* HUH? We did exit, didn't we? */
            exitcode = APEXIT_CHILDFATAL;
        }
        if (   exitcode == APEXIT_CHILDFATAL
            || exitcode == APEXIT_CHILDINIT
            || exitcode == APEXIT_INIT) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "Parent: child process exited with status %u -- Aborting.", exitcode);
            shutdown_pending = 1;
        }
        else {
            int i;
            restart_pending = 1;
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Parent: child process exited with status %u -- Restarting.", exitcode);
            for (i = 0; i < ap_threads_per_child; i++) {
                ap_update_child_status_from_indexes(0, i, SERVER_DEAD, NULL);
            }
        }
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }
    if (restart_pending) {
        ++my_generation;
        ap_scoreboard_image->global->running_generation = my_generation;
    }
die_now:
    if (shutdown_pending)
    {
        int timeout = 30000;  /* Timeout is milliseconds */
        winnt_mpm_state = AP_MPMQ_STOPPING;

        /* This shutdown is only marginally graceful. We will give the
         * child a bit of time to exit gracefully. If the time expires,
         * the child will be wacked.
         */
        if (!strcasecmp(signal_arg, "runservice")) {
            mpm_service_stopping();
        }
        /* Signal the child processes to exit */
        if (SetEvent(child_exit_event) == 0) {
                ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "Parent: SetEvent for child process %d failed", event_handles[CHILD_HANDLE]);
        }
        if (event_handles[CHILD_HANDLE]) {
            rv = WaitForSingleObject(event_handles[CHILD_HANDLE], timeout);
            if (rv == WAIT_OBJECT_0) {
                ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                             "Parent: Child process exited successfully.");
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
            else {
                ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                             "Parent: Forcing termination of child process %d ", event_handles[CHILD_HANDLE]);
                TerminateProcess(event_handles[CHILD_HANDLE], 1);
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
        }
        CloseHandle(child_exit_event);
        return 0;  /* Tell the caller we do not want to restart */
    }
    winnt_mpm_state = AP_MPMQ_STARTING;
    CloseHandle(child_exit_event);
    return 1;      /* Tell the caller we want a restart */
}