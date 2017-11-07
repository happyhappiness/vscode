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
            ap_push_pool(worker_queue_info, p);
            return;
        }
        apr_atomic_inc32(&connection_count);
        apr_pool_cleanup_register(c->pool, cs, decrement_connection_count,
                                  apr_pool_cleanup_null);
        ap_set_module_config(c->conn_config, &mpm_event_module, cs);
        c->current_thread = thd;
        cs->c = c;
        c->cs = &(cs->pub);
        cs->p = p;
        cs->sc = ap_get_module_config(ap_server_conf->module_config,
                                      &mpm_event_module);
        cs->pfd.desc_type = APR_POLL_SOCKET;
        cs->pfd.reqevents = APR_POLLIN;
        cs->pfd.desc.s = sock;
        pt->type = PT_CSD;
        pt->baton = cs;
        cs->pfd.client_data = pt;
        apr_pool_pre_cleanup_register(p, cs, ptrans_pre_cleanup);
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

        cs->pub.sense = CONN_SENSE_DEFAULT;
    }
    else {
        c = cs->c;
        notify_resume(cs, sbh);
        c->current_thread = thd;
        /* Subsequent request on a conn, and thread number is part of ID */
        c->id = conn_id;
    }

    if (c->clogging_input_filters && !c->aborted) {
        /* Since we have an input filter which 'clogs' the input stream,
         * like mod_ssl used to, lets just do the normal read from input
         * filters, like the Worker MPM does. Filters that need to write
         * where they would otherwise read, or read where they would
         * otherwise write, should set the sense appropriately.
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
            cs->queue_timestamp = apr_time_now();
            notify_suspend(cs);
            apr_thread_mutex_lock(timeout_mutex);
            TO_QUEUE_APPEND(cs->sc->wc_q, cs);
            cs->pfd.reqevents = (
                    cs->pub.sense == CONN_SENSE_WANT_READ ? APR_POLLIN :
                            APR_POLLOUT) | APR_POLLHUP | APR_POLLERR;
            cs->pub.sense = CONN_SENSE_DEFAULT;
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
        start_lingering_close_blocking(cs);
    }
    else if (cs->pub.state == CONN_STATE_CHECK_REQUEST_LINE_READABLE) {
        /* It greatly simplifies the logic to use a single timeout value per q
         * because the new element can just be added to the end of the list and
         * it will stay sorted in expiration time sequence.  If brand new
         * sockets are sent to the event thread for a readability check, this
         * will be a slight behavior change - they use the non-keepalive
         * timeout today.  With a normal client, the socket will be readable in
         * a few milliseconds anyway.
         */
        cs->queue_timestamp = apr_time_now();
        notify_suspend(cs);
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_APPEND(cs->sc->ka_q, cs);

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
        notify_suspend(cs);
    }
}