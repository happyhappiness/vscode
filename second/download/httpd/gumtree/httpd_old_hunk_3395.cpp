        else /* (accf = 0)  e.g. 'none' */
        {
            /* There is no socket reuse without AcceptEx() */
            if (context->accept_socket != INVALID_SOCKET)
                closesocket(context->accept_socket);

            /* This could be a persistant event per-listener rather than
             * per-accept.  However, the event needs to be removed from
             * the target socket if not removed from the listen socket
             * prior to accept(), or the event select is inherited.
             * and must be removed from the accepted socket.
             */

            do {
                rv = WaitForMultipleObjectsEx(3, events, FALSE, INFINITE, TRUE);
            } while (rv == WAIT_IO_COMPLETION);


            if (rv != WAIT_OBJECT_0 + 2) {
                /* not FD_ACCEPT; 
                 * exit_event triggered or event handle was closed 
                 */
                break;
            }

            context->sa_client = NULL;
            context->sa_server = (void *) context->buff;
            context->sa_server_len = sizeof(context->buff);
            context->accept_socket = accept(nlsd, context->sa_server,
                                            &context->sa_server_len);

            if (context->accept_socket == INVALID_SOCKET) {

                rv = apr_get_netos_error();
                if (   rv == APR_FROM_OS_ERROR(WSAECONNRESET)
                    || rv == APR_FROM_OS_ERROR(WSAEINPROGRESS)
                    || rv == APR_FROM_OS_ERROR(WSAEWOULDBLOCK) ) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG,
                                 rv, ap_server_conf,
                                 "accept() failed, retrying.");
                    continue;
                }

                /* A more serious error that 'retry', log it */
                ap_log_error(APLOG_MARK, APLOG_WARNING,
                             rv, ap_server_conf,
                             "accept() failed.");

                if (   rv == APR_FROM_OS_ERROR(WSAEMFILE)
                    || rv == APR_FROM_OS_ERROR(WSAENOBUFS) ) {
                    /* Hopefully a temporary condition in the provider? */
                    Sleep(100);
                    ++err_count;
                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                     "Child %d: Encountered too many accept() "
                                     "resource faults, aborting.",
                                     my_pid);
                        break;
                    }
                    continue;
                }
                break;
            }
            /* Per MSDN, cancel the inherited association of this socket 
             * to the WSAEventSelect API, and restore the state corresponding
             * to apr_os_sock_make's default assumptions (really, a flaw within
             * os_sock_make and os_sock_put that it does not query).
             */
            WSAEventSelect(context->accept_socket, 0, 0);
            context->overlapped.Pointer = NULL;
            err_count = 0;
        }

        sockinfo.os_sock = &context->accept_socket;
        sockinfo.local   = context->sa_server;
        sockinfo.remote  = context->sa_client;
        sockinfo.family  = context->sa_server->sa_family;
        sockinfo.type    = SOCK_STREAM;
        /* Restore the state corresponding to apr_os_sock_make's default
         * assumption of timeout -1 (really, a flaw of os_sock_make and 
         * os_sock_put that it does not query to determine ->timeout).
         * XXX: Upon a fix to APR, these three statements should disappear.
         */
        ioctlsocket(context->accept_socket, FIONBIO, &zero);
        setsockopt(context->accept_socket, SOL_SOCKET, SO_RCVTIMEO, 
                   (char *) &zero, sizeof(zero));
        setsockopt(context->accept_socket, SOL_SOCKET, SO_SNDTIMEO, 
                   (char *) &zero, sizeof(zero));
        apr_os_sock_make(&context->sock, &sockinfo, context->ptrans);

        /* When a connection is received, send an io completion notification
         * to the ThreadDispatchIOCP.
         */
