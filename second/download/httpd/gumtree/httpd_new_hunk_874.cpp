
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


/*
 * worker_main()
 * Main entry point for the worker threads. Worker threads block in
 * win*_get_connection() awaiting a connection to service.
 */
static unsigned int __stdcall worker_main(void *thread_num_val)
{
    static int requests_this_child = 0;
    PCOMP_CONTEXT context = NULL;
    int thread_num = (int)thread_num_val;
    ap_sb_handle_t *sbh;

    while (1) {
        conn_rec *c;
        apr_int32_t disconnected;

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

