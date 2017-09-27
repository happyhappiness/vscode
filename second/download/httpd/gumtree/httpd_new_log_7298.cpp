ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02125)
                 "Error: %d with WSAIoctl(SO_TLS_SET_CLIENT)",
                 WSAGetLastError());