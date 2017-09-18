        /* When a connection is received, send an io completion notification to
         * the ThreadDispatchIOCP. This function could be replaced by
         * mpm_post_completion_context(), but why do an extra function call...
         */
        PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_CONNECTION_ACCEPTED,
                                   &context->Overlapped);
    }

    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }
}
static PCOMP_CONTEXT winnt_get_connection(PCOMP_CONTEXT context)
{
    int rc;
    DWORD BytesRead;
    DWORD CompKey;
    LPOVERLAPPED pol;

    mpm_recycle_completion_context(context);

    g_blocked_threads++;        
    while (1) {
        if (workers_may_exit) {
            g_blocked_threads--;
            return NULL;
        }
        rc = GetQueuedCompletionStatus(ThreadDispatchIOCP, &BytesRead, &CompKey,
                                       &pol, INFINITE);
        if (!rc) {
            rc = apr_get_os_error();
