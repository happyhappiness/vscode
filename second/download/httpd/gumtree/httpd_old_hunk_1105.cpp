                      PADDED_ADDR_SIZE,
                      &BytesRead,
                      &context->Overlapped)) {
            rv = apr_get_netos_error();
            if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
                (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {
                /* Hack alert. Occasionally, TransmitFile will not recycle the 
                 * accept socket (usually when the client disconnects early). 
                 * Get a new socket and try the call again.
                 */
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf,
                       "winnt_accept: AcceptEx failed due to early client "
                       "disconnect. Reallocate the accept socket and try again.");
                continue;
            }
            else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
                     (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "winnt_accept: AcceptEx failed. Attempting to recover.");
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                Sleep(100);
                continue;
            }

            /* Wait for pending i/o. 
             * Wake up once per second to check for shutdown .
             * XXX: We should be waiting on exit_event instead of polling
