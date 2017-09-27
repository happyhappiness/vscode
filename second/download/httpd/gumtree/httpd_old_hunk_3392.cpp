                    if (accf == 2)
                        apr_bucket_free(buf);
                    closesocket(context->accept_socket);
                    context->accept_socket = INVALID_SOCKET;
                    ++err_count;
                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                     "Child %d: Encountered too many AcceptEx "
                                     "faults accepting client connections.",
                                     my_pid);
                        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
                                     "winnt_mpm: falling back to "
                                     "'AcceptFilter none'.");
                        err_count = 0;
                        accf = 0;
                        goto reinit;
                    }
