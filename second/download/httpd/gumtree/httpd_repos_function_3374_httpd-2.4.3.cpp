static void process_socket(apr_thread_t *thd, apr_pool_t * p, apr_socket_t * sock,
                          event_conn_state_t * cs, int my_child_num,
                          int my_thread_num)
{
    conn_rec *c;
    long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
    int rc;
    ap_sb_handle_t *sbh;

    /* XXX: This will cause unbounded mem usage for long lasting connections */
    ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);

    if (cs == NULL) {           /* This is a new connection */
        listener_poll_type *pt = apr_pcalloc(p, sizeof(*pt));
        cs = apr_pcalloc(p, sizeof(event_conn_state_t));
        cs->bucket_alloc = apr_bucket_alloc_create(p);
        c = ap_run_create_connection(p, ap_server_conf, sock,
                                     conn_id, sbh, cs->bucket_alloc);
        if (!c) {
            apr_bucket_alloc_destroy(cs->bucket_alloc);
            apr_pool_clear(p);
            ap_push_pool(worker_queue_info, p);
            return;
        }
        apr_atomic_inc32(&connection_count);
        apr_pool_cleanup_register(c->pool, cs, decrement_connection_count,
                                  apr_pool_cleanup_null);
        c->current_thread = thd;
        cs->c = c;
        c->cs = &(cs->pub);
        cs->p = p;
        cs->pfd.desc_type = APR_POLL_SOCKET;
        cs->pfd.reqevents = APR_POLLIN;
        cs->pfd.desc.s = sock;
        pt->type = PT_CSD;
        pt->baton = cs;
        cs->pfd.client_data = pt;
        TO_QUEUE_ELEM_INIT(cs);

        ap_update_vhost_given_ip(c);

        rc = ap_run_pre_connection(c, sock);
        if (rc != OK && rc != DONE) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(00469)
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
        cs->pub.state = CONN_STATE_READ_REQUEST_LINE;

    }
    else {
        c = cs->c;
        c->sbh = sbh;
        c->current_thread = thd;
    }

    if (c->clogging_input_filters && !c->aborted) {
        /* Since we have an input filter which 'cloggs' the input stream,
         * like mod_ssl, lets just do the normal read from input filters,
         * like the Worker MPM does.
         */
        apr_atomic_inc32(&clogged_count);
        ap_run_process_connection(c);
        if (cs->pub.state != CONN_STATE_SUSPENDED) {
            cs->pub.state = CONN_STATE_LINGER;
        }
        apr_atomic_dec32(&clogged_count);
    }

read_request:
    if (cs->pub.state == CONN_STATE_READ_REQUEST_LINE) {
        if (!c->aborted) {
            ap_run_process_connection(c);

            /* state will be updated upon return
             * fall thru to either wait for readability/timeout or
             * do lingering close
             */
        }
        else {
            cs->pub.state = CONN_STATE_LINGER;
        }
    }

    if (cs->pub.state == CONN_STATE_WRITE_COMPLETION) {
        ap_filter_t *output_filter = c->output_filters;
        apr_status_t rv;
        ap_update_child_status_from_conn(sbh, SERVER_BUSY_WRITE, c);
        while (output_filter->next != NULL) {
            output_filter = output_filter->next;
        }
        rv = output_filter->frec->filter_func.out_func(output_filter, NULL);
        if (rv != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, APLOGNO(00470)
                          "network write failure in core output filter");
            cs->pub.state = CONN_STATE_LINGER;
        }
        else if (c->data_in_output_filters) {
            /* Still in WRITE_COMPLETION_STATE:
             * Set a write timeout for this connection, and let the
             * event thread poll for writeability.
             */
            cs->expiration_time = ap_server_conf->timeout + apr_time_now();
            apr_thread_mutex_lock(timeout_mutex);
            TO_QUEUE_APPEND(write_completion_q, cs);
            cs->pfd.reqevents = APR_POLLOUT | APR_POLLHUP | APR_POLLERR;
            rc = apr_pollset_add(event_pollset, &cs->pfd);
            apr_thread_mutex_unlock(timeout_mutex);
            return;
        }
        else if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted ||
            listener_may_exit) {
            cs->pub.state = CONN_STATE_LINGER;
        }
        else if (c->data_in_input_filters) {
            cs->pub.state = CONN_STATE_READ_REQUEST_LINE;
            goto read_request;
        }
        else {
            cs->pub.state = CONN_STATE_CHECK_REQUEST_LINE_READABLE;
        }
    }

    if (cs->pub.state == CONN_STATE_LINGER) {
        if (!start_lingering_close_blocking(cs))
            return;
    }
    else if (cs->pub.state == CONN_STATE_CHECK_REQUEST_LINE_READABLE) {
        apr_status_t rc;

        /* It greatly simplifies the logic to use a single timeout value here
         * because the new element can just be added to the end of the list and
         * it will stay sorted in expiration time sequence.  If brand new
         * sockets are sent to the event thread for a readability check, this
         * will be a slight behavior change - they use the non-keepalive
         * timeout today.  With a normal client, the socket will be readable in
         * a few milliseconds anyway.
         */
        cs->expiration_time = ap_server_conf->keep_alive_timeout +
                              apr_time_now();
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_APPEND(keepalive_q, cs);

        /* Add work to pollset. */
        cs->pfd.reqevents = APR_POLLIN;
        rc = apr_pollset_add(event_pollset, &cs->pfd);
        apr_thread_mutex_unlock(timeout_mutex);

        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                         "process_socket: apr_pollset_add failure");
            AP_DEBUG_ASSERT(rc == APR_SUCCESS);
        }
    }
    else if (cs->pub.state == CONN_STATE_SUSPENDED) {
        apr_atomic_inc32(&suspended_count);
    }
    /*
     * Prevent this connection from writing to our connection state after it
     * is no longer associated with this thread. This would happen if the EOR
     * bucket is destroyed from the listener thread due to a connection abort
     * or timeout.
     */
    c->sbh = NULL;

    return;
}