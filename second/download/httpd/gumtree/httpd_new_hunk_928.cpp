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

    return 0;
}


static void cleanup_thread(HANDLE *handles, int *thread_cnt, int thread_to_clean)
{
