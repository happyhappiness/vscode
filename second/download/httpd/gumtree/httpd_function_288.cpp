static void process_socket(apr_pool_t *p, apr_socket_t *sock, int my_child_num,
                           int my_thread_num, apr_bucket_alloc_t *bucket_alloc)
{
    conn_rec *current_conn;
    long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
    int csd;
    ap_sb_handle_t *sbh;

    ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);
    apr_os_sock_get(&csd, sock);

    if (csd >= FD_SETSIZE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "new file descriptor %d is too large; you probably need "
                     "to rebuild Apache with a larger FD_SETSIZE "
                     "(currently %d)", 
                     csd, FD_SETSIZE);
        apr_socket_close(sock);
        return;
    }

    current_conn = ap_run_create_connection(p, ap_server_conf, sock,
                                            conn_id, sbh, bucket_alloc);
    if (current_conn) {
        ap_process_connection(current_conn, sock);
        ap_lingering_close(current_conn);
    }
}