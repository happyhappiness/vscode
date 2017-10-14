static void worker_main(long thread_num)
{
    static int requests_this_child = 0;
    PCOMP_CONTEXT context = NULL;
    ap_sb_handle_t *sbh;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %d starting.", my_pid, thread_num);
    while (1) {
        conn_rec *c;
        apr_int32_t disconnected;

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

        /* Grab a connection off the network */
        if (use_acceptex) {
            context = winnt_get_connection(context);
        }
        else {
            context = win9x_get_connection(context);
        }
        if (!context) {
            /* Time for the thread to exit */
            break;
        }

        /* Have we hit MaxRequestPerChild connections? */
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

        if (c) {
            ap_process_connection(c, context->sock);
            apr_socket_opt_get(context->sock, APR_SO_DISCONNECTED, 
                               &disconnected);
            if (!disconnected) {
                context->accept_socket = INVALID_SOCKET;
                ap_lingering_close(c);
            }
            else if (!use_acceptex) {
                /* If the socket is disconnected but we are not using acceptex, 
                 * we cannot reuse the socket. Disconnected sockets are removed
                 * from the apr_socket_t struct by apr_sendfile() to prevent the
                 * socket descriptor from being inadvertently closed by a call 
                 * to apr_socket_close(), so close it directly.
                 */
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
            }
        }
        else {
            /* ap_run_create_connection closes the socket on failure */
            context->accept_socket = INVALID_SOCKET;
        }
    }

    ap_update_child_status_from_indexes(0, thread_num, SERVER_DEAD, 
                                        (request_rec *) NULL);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %d exiting.", my_pid, thread_num);
}