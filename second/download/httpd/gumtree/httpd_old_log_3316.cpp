ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_SERVER)", WSAGetLastError());