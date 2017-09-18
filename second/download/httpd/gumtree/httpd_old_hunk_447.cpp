
    if ((rv = apr_os_sock_get(&csd, sock)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, "apr_os_sock_get");
    }

    if (csd >= FD_SETSIZE) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, NULL,
                     "new file descriptor %d is too large; you probably need "
                     "to rebuild Apache with a larger FD_SETSIZE "
                     "(currently %d)", 
                     csd, FD_SETSIZE);
        apr_socket_close(sock);
        return;
