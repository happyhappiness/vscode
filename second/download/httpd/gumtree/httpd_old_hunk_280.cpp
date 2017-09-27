    ap_sb_handle_t *sbh;

    if ((rv = apr_os_sock_get(&csd, sock)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL, "apr_os_sock_get");
    }

    if (csd >= FD_SETSIZE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "new file descriptor %d is too large; you probably need "
                     "to rebuild Apache with a larger FD_SETSIZE "
                     "(currently %d)", 
                     csd, FD_SETSIZE);
        apr_socket_close(sock);
        return;
    }

    if (thread_socket_table[thread_num] < 0) {
        ap_sock_disable_nagle(sock);
    }

    ap_create_sb_handle(&sbh, p, conn_id / thread_limit, thread_num);
    current_conn = ap_run_create_connection(p, ap_server_conf, sock, conn_id, 
