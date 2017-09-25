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
