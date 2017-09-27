    /* turn on ssl for the socket */
        ulFlags = (numcerts ? SO_TLS_ENABLE : SO_TLS_ENABLE | SO_TLS_BLIND_ACCEPT);
        rcode = WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
                     NULL, 0, NULL, NULL, NULL);
        if (SOCKET_ERROR == rcode)
        {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02124)
                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
                return rcode;
        }

    ulFlags = SO_TLS_UNCLEAN_SHUTDOWN;
        WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
