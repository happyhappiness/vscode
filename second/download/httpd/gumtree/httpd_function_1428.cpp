static unsigned int __stdcall winnt_accept(void *lr_)
{
    ap_listen_rec *lr = (ap_listen_rec *)lr_;
    apr_os_sock_info_t sockinfo;
    PCOMP_CONTEXT context = NULL;
    DWORD BytesRead;
    SOCKET nlsd;
    int rv, err_count = 0;
#if APR_HAVE_IPV6
    SOCKADDR_STORAGE ss_listen;
    int namelen = sizeof(ss_listen);
#endif

    apr_os_sock_get(&nlsd, lr->sd);

#if APR_HAVE_IPV6
    if (getsockname(nlsd, (struct sockaddr *)&ss_listen, &namelen) == SOCKET_ERROR) {
        ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_netos_error(), ap_server_conf,
                    "winnt_accept: getsockname error on listening socket, is IPv6 available?");
        return 1;
   }
#endif

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                 "Child %d: Starting thread to listen on port %d.", my_pid, lr->bind_addr->port);
    while (!shutdown_in_progress) {
        if (!context) {
            context = mpm_get_completion_context();
            if (!context) {
                /* Temporary resource constraint? */
                Sleep(0);
                continue;
            }
        }

        /* Create and initialize the accept socket */
#if APR_HAVE_IPV6
        if (context->accept_socket == INVALID_SOCKET) {
            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
            context->socket_family = ss_listen.ss_family;
        }
        else if (context->socket_family != ss_listen.ss_family) {
            closesocket(context->accept_socket);
            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
            context->socket_family = ss_listen.ss_family;
        }

        if (context->accept_socket == INVALID_SOCKET) {
            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "winnt_accept: Failed to allocate an accept socket. "
                         "Temporary resource constraint? Try again.");
            Sleep(100);
            continue;
        }
#else
        if (context->accept_socket == INVALID_SOCKET) {
            context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (context->accept_socket == INVALID_SOCKET) {
                /* Another temporary condition? */
                ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                             "winnt_accept: Failed to allocate an accept socket. "
                             "Temporary resource constraint? Try again.");
                Sleep(100);
                continue;
            }
        }
#endif
        /* AcceptEx on the completion context. The completion context will be
         * signaled when a connection is accepted.
         */
        if (!AcceptEx(nlsd, context->accept_socket,
                      context->buff,
                      0,
                      PADDED_ADDR_SIZE,
                      PADDED_ADDR_SIZE,
                      &BytesRead,
                      &context->Overlapped)) {
            rv = apr_get_netos_error();
            if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
                (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {
                /* We can get here when:
                 * 1) the client disconnects early
                 * 2) TransmitFile does not properly recycle the accept socket (typically
                 *    because the client disconnected)
                 * 3) there is VPN or Firewall software installed with buggy AcceptEx implementation
                 * 4) the webserver is using a dynamic address that has changed
                 */
                ++err_count;
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                 "Child %d: Encountered too many errors accepting client connections. "
                                 "Possible causes: dynamic address renewal, or incompatible VPN or firewall software. "
                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
                    err_count = 0;
                }
                continue;
            }
            else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
                     (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
                ++err_count;
                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                    ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                 "Child %d: Encountered too many errors accepting client connections. "
                                 "Possible causes: Unknown. "
                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
                    err_count = 0;
                }
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                continue;
            }
            err_count = 0;

            /* Wait for pending i/o.
             * Wake up once per second to check for shutdown .
             * XXX: We should be waiting on exit_event instead of polling
             */
            while (1) {
                rv = WaitForSingleObject(context->Overlapped.hEvent, 1000);
                if (rv == WAIT_OBJECT_0) {
                    if (context->accept_socket == INVALID_SOCKET) {
                        /* socket already closed */
                        break;
                    }
                    if (!GetOverlappedResult((HANDLE)context->accept_socket,
                                             &context->Overlapped,
                                             &BytesRead, FALSE)) {
                        ap_log_error(APLOG_MARK, APLOG_WARNING,
                                     apr_get_os_error(), ap_server_conf,
                             "winnt_accept: Asynchronous AcceptEx failed.");
                        closesocket(context->accept_socket);
                        context->accept_socket = INVALID_SOCKET;
                    }
                    break;
                }
                /* WAIT_TIMEOUT */
                if (shutdown_in_progress) {
                    closesocket(context->accept_socket);
                    context->accept_socket = INVALID_SOCKET;
                    break;
                }
            }
            if (context->accept_socket == INVALID_SOCKET) {
                continue;
            }
        }
        err_count = 0;
        /* Inherit the listen socket settings. Required for
         * shutdown() to work
         */
        if (setsockopt(context->accept_socket, SOL_SOCKET,
                       SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
                       sizeof(nlsd))) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");
            /* Not a failure condition. Keep running. */
        }

        /* Get the local & remote address */
        GetAcceptExSockaddrs(context->buff,
                             0,
                             PADDED_ADDR_SIZE,
                             PADDED_ADDR_SIZE,
                             &context->sa_server,
                             &context->sa_server_len,
                             &context->sa_client,
                             &context->sa_client_len);

        sockinfo.os_sock = &context->accept_socket;
        sockinfo.local   = context->sa_server;
        sockinfo.remote  = context->sa_client;
        sockinfo.family  = context->sa_server->sa_family;
        sockinfo.type    = SOCK_STREAM;
        apr_os_sock_make(&context->sock, &sockinfo, context->ptrans);

        /* When a connection is received, send an io completion notification to
         * the ThreadDispatchIOCP. This function could be replaced by
         * mpm_post_completion_context(), but why do an extra function call...
         */
        PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_CONNECTION_ACCEPTED,
                                   &context->Overlapped);
        context = NULL;
    }
    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
                 "Child %d: Accept thread exiting.", my_pid);
    return 0;
}