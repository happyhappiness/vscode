                        accf = 0;
                    }
                    continue;
                }
                else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
                         (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
                    closesocket(context->accept_socket);
                    context->accept_socket = INVALID_SOCKET;
                    ++err_count;
                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00339)
                                     "Child: Encountered too many AcceptEx "
