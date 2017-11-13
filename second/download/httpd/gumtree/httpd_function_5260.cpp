void get_listeners_from_parent(server_rec *s)
{
    WSAPROTOCOL_INFO WSAProtocolInfo;
    ap_listen_rec *lr;
    DWORD BytesRead;
    int lcnt = 0;
    SOCKET nsd;

    /* Set up a default listener if necessary */
    if (ap_listeners == NULL) {
        ap_listen_rec *lr;
        lr = apr_palloc(s->process->pool, sizeof(ap_listen_rec));
        lr->sd = NULL;
        lr->next = ap_listeners;
        ap_listeners = lr;
    }

    /* Open the pipe to the parent process to receive the inherited socket
     * data. The sockets have been set to listening in the parent process.
     *
     * *** We now do this was back in winnt_rewrite_args
     * pipe = GetStdHandle(STD_INPUT_HANDLE);
     */
    for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
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