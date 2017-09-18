                      context->buff,
                      0,
                      PADDED_ADDR_SIZE, 
                      PADDED_ADDR_SIZE,
                      &BytesRead,
                      &context->Overlapped)) {
            lasterror = apr_get_netos_error();
            if (lasterror == APR_FROM_OS_ERROR(WSAEINVAL)) {
                /* Hack alert. Occasionally, TransmitFile will not recycle the 
                 * accept socket (usually when the client disconnects early). 
                 * Get a new socket and try the call again.
                 */
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, lasterror, ap_server_conf,
                       "winnt_accept: AcceptEx failed due to early client "
                       "disconnect. Reallocate the accept socket and try again.");
                if (shutdown_in_progress)
                    break;
                else
                    goto again;
            }
            else if (lasterror != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) {
                ap_log_error(APLOG_MARK,APLOG_ERR, lasterror, ap_server_conf,
                             "winnt_accept: AcceptEx failed. Attempting to recover.");
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                Sleep(100);
                goto again;
            }

            /* Wait for pending i/o */
            WaitForSingleObject(context->Overlapped.hEvent, INFINITE);
        }

        /* ### There is a race condition here.  The mainline may hit 
         * WSATerminate before this thread reawakens.  Look First.
         */
        if (shutdown_in_progress) {
            break;
        }

        /* Inherit the listen socket settings. Required for 
         * shutdown() to work 
         */
        if (setsockopt(context->accept_socket, SOL_SOCKET,
