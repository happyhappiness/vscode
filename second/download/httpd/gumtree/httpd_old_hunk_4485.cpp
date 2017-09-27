            /* Per MSDN, cancel the inherited association of this socket
             * to the WSAEventSelect API, and restore the state corresponding
             * to apr_os_sock_make's default assumptions (really, a flaw within
             * os_sock_make and os_sock_put that it does not query).
             */
            WSAEventSelect(context->accept_socket, 0, 0);
            context->overlapped.Pointer = NULL;
            err_count = 0;

            context->sa_server_len = sizeof(context->buff) / 2;
            if (getsockname(context->accept_socket, context->sa_server,
                            &context->sa_server_len) == SOCKET_ERROR) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf, APLOGNO(00346)
