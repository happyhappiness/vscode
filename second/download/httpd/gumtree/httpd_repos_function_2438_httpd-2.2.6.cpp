static int process_socket(apr_pool_t * p, apr_socket_t * sock,
                          conn_state_t * cs, int my_child_num,
                          int my_thread_num)
{
    conn_rec *c;
    listener_poll_type *pt;
    long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
    int csd;
    int rc;
    apr_time_t time_now = 0;
    ap_sb_handle_t *sbh;

    ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);
    apr_os_sock_get(&csd, sock);

    time_now = apr_time_now();

    if (cs == NULL) {           /* This is a new connection */

        cs = apr_pcalloc(p, sizeof(conn_state_t));

        pt = apr_pcalloc(p, sizeof(*pt));

        cs->bucket_alloc = apr_bucket_alloc_create(p);
        c = ap_run_create_connection(p, ap_server_conf, sock,
                                     conn_id, sbh, cs->bucket_alloc);
        cs->c = c;
        c->cs = cs;
        cs->p = p;
        cs->pfd.desc_type = APR_POLL_SOCKET;
        cs->pfd.reqevents = APR_POLLIN;
        cs->pfd.desc.s = sock;
        pt->type = PT_CSD;
        pt->status = 1;
        pt->baton = cs;
        cs->pfd.client_data = pt;

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
         * and there are measurable delays before the
         * socket is readable due to the first data packet arriving,
         * it might be better to create the cs on the listener thread
         * with the state set to CONN_STATE_CHECK_REQUEST_LINE_READABLE
         *
         * FreeBSD users will want to enable the HTTP accept filter
         * module in their kernel for the highest performance
         * When the accept filter is active, sockets are kept in the
         * kernel until a HTTP request is received.
         */
        cs->state = CONN_STATE_READ_REQUEST_LINE;

    }
    else {
        c = cs->c;
        c->sbh = sbh;
    }

    if (cs->state == CONN_STATE_READ_REQUEST_LINE) {
        if (!c->aborted) {
            ap_run_process_connection(c);

            /* state will be updated upon return
             * fall thru to either wait for readability/timeout or
             * do lingering close
             */
        }
        else {
            cs->state = CONN_STATE_LINGER;
        }
    }

    if (cs->state == CONN_STATE_LINGER) {
        ap_lingering_close(c);
        apr_bucket_alloc_destroy(cs->bucket_alloc);
        apr_pool_clear(p);
        ap_push_pool(worker_queue_info, p);
        return 1;
    }
    else if (cs->state == CONN_STATE_CHECK_REQUEST_LINE_READABLE) {
        apr_status_t rc;
        listener_poll_type *pt = (listener_poll_type *) cs->pfd.client_data;

        /* It greatly simplifies the logic to use a single timeout value here
         * because the new element can just be added to the end of the list and
         * it will stay sorted in expiration time sequence.  If brand new
         * sockets are sent to the event thread for a readability check, this
         * will be a slight behavior change - they use the non-keepalive
         * timeout today.  With a normal client, the socket will be readable in
         * a few milliseconds anyway.
         */
        cs->expiration_time = ap_server_conf->keep_alive_timeout + time_now;
        apr_thread_mutex_lock(timeout_mutex);
        APR_RING_INSERT_TAIL(&timeout_head, cs, conn_state_t, timeout_list);

        pt->status = 0;
        /* Add work to pollset. These are always read events */
        rc = apr_pollset_add(event_pollset, &cs->pfd);

        apr_thread_mutex_unlock(timeout_mutex);

        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                         "process_socket: apr_pollset_add failure");
            AP_DEBUG_ASSERT(rc == APR_SUCCESS);
        }
    }
    return 0;
}