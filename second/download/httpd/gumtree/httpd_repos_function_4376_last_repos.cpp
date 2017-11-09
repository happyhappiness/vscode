static DWORD __stdcall worker_main(void *thread_num_val)
{
    apr_thread_t *thd;
    apr_os_thread_t osthd;
    static int requests_this_child = 0;
    winnt_conn_ctx_t *context = NULL;
    int thread_num = (int)thread_num_val;
    ap_sb_handle_t *sbh;
    conn_rec *c;
    apr_int32_t disconnected;

    osthd = apr_os_thread_current();

    while (1) {

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

        /* Grab a connection off the network */
        context = winnt_get_connection(context);

        if (!context) {
            /* Time for the thread to exit */
            break;
        }

        /* Have we hit MaxConnectionsPerChild connections? */
        if (ap_max_requests_per_child) {
            requests_this_child++;
            if (requests_this_child > ap_max_requests_per_child) {
                SetEvent(max_requests_per_child_event);
            }
        }

        ap_create_sb_handle(&sbh, context->ptrans, 0, thread_num);
        c = ap_run_create_connection(context->ptrans, ap_server_conf,
                                     context->sock, thread_num, sbh,
                                     context->ba);

        if (!c) {
            /* ap_run_create_connection closes the socket on failure */
            context->accept_socket = INVALID_SOCKET;
            continue;
        }

        thd = NULL;
        apr_os_thread_put(&thd, &osthd, context->ptrans);
        c->current_thread = thd;

        ap_process_connection(c, context->sock);

        ap_lingering_close(c);

        apr_socket_opt_get(context->sock, APR_SO_DISCONNECTED, &disconnected);
        if (!disconnected) {
            context->accept_socket = INVALID_SOCKET;
        }
    }

    ap_update_child_status_from_indexes(0, thread_num, SERVER_DEAD, NULL);

    return 0;
}