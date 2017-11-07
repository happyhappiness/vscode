ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02124)
                     "Error: %d with WSAIoctl(flag SO_TLS_ENABLE)",
                     WSAGetLastError());