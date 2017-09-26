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
