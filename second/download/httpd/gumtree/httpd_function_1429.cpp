static PCOMP_CONTEXT winnt_get_connection(PCOMP_CONTEXT context)
{
    int rc;
    DWORD BytesRead;
    LPOVERLAPPED pol;
#ifdef _WIN64
    ULONG_PTR CompKey;
#else
    DWORD CompKey;
#endif

    mpm_recycle_completion_context(context);

    apr_atomic_inc32(&g_blocked_threads);
    while (1) {
        if (workers_may_exit) {
            apr_atomic_dec32(&g_blocked_threads);
            return NULL;
        }
        rc = GetQueuedCompletionStatus(ThreadDispatchIOCP, &BytesRead, &CompKey,
                                       &pol, INFINITE);
        if (!rc) {
            rc = apr_get_os_error();
            ap_log_error(APLOG_MARK,APLOG_DEBUG, rc, ap_server_conf,
                             "Child %d: GetQueuedComplationStatus returned %d", my_pid, rc);
            continue;
        }

        switch (CompKey) {
        case IOCP_CONNECTION_ACCEPTED:
            context = CONTAINING_RECORD(pol, COMP_CONTEXT, Overlapped);
            break;
        case IOCP_SHUTDOWN:
            apr_atomic_dec32(&g_blocked_threads);
            return NULL;
        default:
            apr_atomic_dec32(&g_blocked_threads);
            return NULL;
        }
        break;
    }
    apr_atomic_dec32(&g_blocked_threads);

    return context;
}