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
                         "Child %lu: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
            exit(APEXIT_CHILDINIT);
        }

        if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            HANDLE hProcess = GetCurrentProcess();
            HANDLE dup;
            if (DuplicateHandle(hProcess, (HANDLE) nsd, hProcess, &dup,
                                0, FALSE, DUPLICATE_SAME_ACCESS)) {
                closesocket(nsd);
                nsd = (SOCKET) dup;
            }
        }
        else {
            /* A different approach.  Many users report errors such as
             * (32538)An operation was attempted on something that is not
             * a socket.  : Parent: WSADuplicateSocket failed...
             *
             * This appears that the duplicated handle is no longer recognized
             * as a socket handle.  SetHandleInformation should overcome that
             * problem by not altering the handle identifier.  But this won't
             * work on 9x - it's unsupported.
             */
            if (!SetHandleInformation((HANDLE)nsd, HANDLE_FLAG_INHERIT, 0)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "set_listeners_noninheritable: SetHandleInformation failed.");
            }
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Child %lu: retrieved %d listeners from parent", my_pid, lcnt);
}


static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                   apr_file_t *child_in)
{
