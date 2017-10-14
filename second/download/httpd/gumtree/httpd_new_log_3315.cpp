ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02127)
                     "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_SERVER)", WSAGetLastError());