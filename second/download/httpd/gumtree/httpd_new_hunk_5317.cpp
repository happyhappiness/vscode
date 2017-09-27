     */
    while (1) {
#if !APR_HAS_OTHER_CHILD
        rv = WaitForMultipleObjects(num_events, (HANDLE *)child_events, FALSE, INFINITE);
        cld = rv - WAIT_OBJECT_0;
#else
        /* THIS IS THE EXPECTED BUILD VARIATION -- APR_HAS_OTHER_CHILD */
        rv = WaitForMultipleObjects(num_events, (HANDLE *)child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_refresh_all(APR_OC_REASON_RUNNING);
        }
        else
#endif
            if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                         ap_server_conf, APLOGNO(00356)
                         "Child: WAIT_FAILED -- shutting down server");
            /* check handle validity to identify a possible culprit */
            for (i = 0; i < num_events; i++) {
                DWORD out_flags;

                if (0 == GetHandleInformation(child_events[i], &out_flags)) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                                 ap_server_conf, APLOGNO(02644)
                                 "Child: Event handle #%d (%pp) is invalid",
                                 i, child_events[i]);
                }
            }
            break;
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00357)
                         "Child: Exit event signaled. Child process is "
