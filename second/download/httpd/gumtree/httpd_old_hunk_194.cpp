     *    This event is signaled by the worker threads to indicate that
     *    the process has handled MaxRequestsPerChild connections.
     *
     * TIMEOUT:
     *    To do periodic maintenance on the server (check for thread exits,
     *    number of completion contexts, etc.)
     */
    while (1) {
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %d: WAIT_FAILED -- shutting down server");
            break;
        }
        else if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_check();
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %d: Exit event signaled. Child process is ending.", my_pid);
            break;
        }
