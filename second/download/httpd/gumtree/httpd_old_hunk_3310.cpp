    apr_signal(SIGPIPE, SIG_IGN);
#endif /* SIGPIPE */

#endif
}

/*****************************************************************
 * Child process main loop.
 */

static int process_socket(apr_thread_t *thd, apr_pool_t * p, apr_socket_t * sock,
                          conn_state_t * cs, int my_child_num,
                          int my_thread_num)
{
    conn_rec *c;
    listener_poll_type *pt;
    long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
    int rc;
    ap_sb_handle_t *sbh;

    ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);

    if (cs == NULL) {           /* This is a new connection */

        cs = apr_pcalloc(p, sizeof(conn_state_t));

        pt = apr_pcalloc(p, sizeof(*pt));

        cs->bucket_alloc = apr_bucket_alloc_create(p);
        c = ap_run_create_connection(p, ap_server_conf, sock,
                                     conn_id, sbh, cs->bucket_alloc);
        c->current_thread = thd;
        cs->c = c;
        c->cs = cs;
        cs->p = p;
        cs->pfd.desc_type = APR_POLL_SOCKET;
        cs->pfd.reqevents = APR_POLLIN;
        cs->pfd.desc.s = sock;
        pt->type = PT_CSD;
        pt->bypass_push = 1;
        pt->baton = cs;
        cs->pfd.client_data = pt;
        APR_RING_ELEM_INIT(cs, timeout_list);

        ap_update_vhost_given_ip(c);

        rc = ap_run_pre_connection(c, sock);
        if (rc != OK && rc != DONE) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                         "process_socket: connection aborted");
            c->aborted = 1;
        }

        /**
         * XXX If the platform does not have a usable way of bundling
         * accept() with a socket readability check, like Win32,
