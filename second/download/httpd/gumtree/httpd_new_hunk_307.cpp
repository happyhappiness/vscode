     *    This event is signaled by the worker threads to indicate that
     *    the process has handled MaxRequestsPerChild connections.
     *
     * TIMEOUT:
     *    To do periodic maintenance on the server (check for thread exits,
     *    number of completion contexts, etc.)
     *
     * XXX: thread exits *aren't* being checked.
     *
     * XXX: other_child - we need the process handles to the other children
     *      in order to map them to apr_proc_other_child_read (which is not
     *      named well, it's more like a_p_o_c_died.)
     *
     * XXX: however - if we get a_p_o_c handle inheritance working, and
     *      the parent process creates other children and passes the pipes 
     *      to our worker processes, then we have no business doing such 
     *      things in the child_main loop, but should happen in master_main.
     */
    while (1) {
#if !APR_HAS_OTHER_CHILD
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, INFINITE);
        cld = rv - WAIT_OBJECT_0;
#else
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_check();
        }
        else 
#endif
            if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %d: WAIT_FAILED -- shutting down server", my_pid);
            break;
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %d: Exit event signaled. Child process is ending.", my_pid);
            break;
        }
