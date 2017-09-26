                 */
                ++err_count;
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                 "Child %lu: Encountered too many errors accepting client connections. "
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
                                 "Child %lu: Encountered too many errors accepting client connections. "
                                 "Possible causes: Unknown. "
                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
                    err_count = 0;
                }
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
