                }
                continue;
            }
            else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
                     (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
                ++err_count;
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                if (err_count > MAX_ACCEPTEX_ERR_COUNT) { 
                    ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                 "Child %d: Encountered too many errors accepting client connections. "
                                 "Possible causes: Unknown. "
                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
                    err_count = 0;
                }
                continue;
            }

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
