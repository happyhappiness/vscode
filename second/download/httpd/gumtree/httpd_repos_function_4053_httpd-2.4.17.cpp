static void process_socket(apr_thread_t *thd, apr_pool_t *p, apr_socket_t *sock,
                           int my_child_num,
                           int my_thread_num, apr_bucket_alloc_t *bucket_alloc)
{
    conn_rec *current_conn;
    long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
    ap_sb_handle_t *sbh;

    ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);

    current_conn = ap_run_create_connection(p, ap_server_conf, sock,
                                            conn_id, sbh, bucket_alloc);
    if (current_conn) {
        current_conn->current_thread = thd;
        ap_process_connection(current_conn, sock);
        ap_lingering_close(current_conn);
    }
}