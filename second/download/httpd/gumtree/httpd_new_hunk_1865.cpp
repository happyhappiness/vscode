        if (!ReadFile(pipe, &WSAProtocolInfo, sizeof(WSAPROTOCOL_INFO),
                      &BytesRead, (LPOVERLAPPED) NULL)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "setup_inherited_listeners: Unable to read socket data from parent");
            exit(APEXIT_CHILDINIT);
        }

        nsd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
                        &WSAProtocolInfo, 0, 0);
        if (nsd == INVALID_SOCKET) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
                         "Child %d: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
            exit(APEXIT_CHILDINIT);
        }

        if (!SetHandleInformation((HANDLE)nsd, HANDLE_FLAG_INHERIT, 0)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
                         "set_listeners_noninheritable: SetHandleInformation failed.");
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Child %d: retrieved %d listeners from parent", my_pid, lcnt);
}


static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                   apr_file_t *child_in)
{
