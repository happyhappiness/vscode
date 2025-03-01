     * for the target process then send the WSAPROTOCOL_INFO
     * (returned by dup socket) to the child.
     */
    for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
        apr_os_sock_t nsd;
        lpWSAProtocolInfo = apr_pcalloc(p, sizeof(WSAPROTOCOL_INFO));
        apr_os_sock_get(&nsd, lr->sd);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00408)
                     "Parent: Duplicating socket %d (%pI) and sending it to child process %lu",
                     nsd, lr->bind_addr, dwProcessId);
        if (WSADuplicateSocket(nsd, dwProcessId,
                               lpWSAProtocolInfo) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf, APLOGNO(00409)
                         "Parent: WSADuplicateSocket failed for socket %d. Check the FAQ.", nsd);
            return -1;
        }

        if ((rv = apr_file_write_full(child_in, lpWSAProtocolInfo,
                                      sizeof(WSAPROTOCOL_INFO), &BytesWritten))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00410)
                         "Parent: Unable to write duplicated socket %d to the child.", nsd);
            return -1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00411)
                 "Parent: Sent %d listeners to child %lu", lcnt, dwProcessId);
    return 0;
}

enum waitlist_e {
    waitlist_ready = 0,
    waitlist_term = 1
