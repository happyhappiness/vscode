#define CHILD_HANDLE     0
#define SHUTDOWN_HANDLE  1
#define RESTART_HANDLE   2
static int master_main(server_rec *s, HANDLE shutdown_event, HANDLE restart_event)
{
    int rv, cld;
    int child_created;
    int restart_pending;
    int shutdown_pending;
    HANDLE child_exit_event;
    HANDLE event_handles[NUM_WAIT_HANDLES];
    DWORD child_pid;

    child_created = restart_pending = shutdown_pending = 0;

    event_handles[SHUTDOWN_HANDLE] = shutdown_event;
    event_handles[RESTART_HANDLE] = restart_event;

    /* Create a single child process */
    rv = create_process(pconf, &event_handles[CHILD_HANDLE],
                        &child_exit_event, &child_pid);
    if (rv < 0)
    {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00419)
                     "master_main: create child process failed. Exiting.");
        shutdown_pending = 1;
        goto die_now;
    }

    child_created = 1;

    if (!strcasecmp(signal_arg, "runservice")) {
        mpm_service_started();
    }

    /* Update the scoreboard. Note that there is only a single active
     * child at once.
     */
    ap_scoreboard_image->parent[0].quiescing = 0;
    winnt_note_child_started(/* slot */ 0, child_pid);

    /* Wait for shutdown or restart events or for child death */
    winnt_mpm_state = AP_MPMQ_RUNNING;
    rv = WaitForMultipleObjects(NUM_WAIT_HANDLES, (HANDLE *) event_handles, FALSE, INFINITE);
    cld = rv - WAIT_OBJECT_0;
    if (rv == WAIT_FAILED) {
        /* Something serious is wrong */
        ap_log_error(APLOG_MARK,APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00420)
                     "master_main: WaitForMultipleObjects WAIT_FAILED -- doing server shutdown");
        shutdown_pending = 1;
    }
    else if (rv == WAIT_TIMEOUT) {
        /* Hey, this cannot happen */
        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00421)
                     "master_main: WaitForMultipleObjects with INFINITE wait exited with WAIT_TIMEOUT");
        shutdown_pending = 1;
    }
    else if (cld == SHUTDOWN_HANDLE) {
        /* shutdown_event signalled */
        shutdown_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, s, APLOGNO(00422)
                     "Parent: Received shutdown signal -- Shutting down the server.");
        if (ResetEvent(shutdown_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00423)
                         "ResetEvent(shutdown_event)");
        }
    }
    else if (cld == RESTART_HANDLE) {
        /* Received a restart event. Prepare the restart_event to be reused
         * then signal the child process to exit.
         */
        restart_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(00424)
                     "Parent: Received restart signal -- Restarting the server.");
        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00425)
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00426)
                         "Parent: SetEvent for child process %pp failed.",
                         event_handles[CHILD_HANDLE]);
        }
        /* Don't wait to verify that the child process really exits,
         * just move on with the restart.
         */
        CloseHandle(event_handles[CHILD_HANDLE]);
