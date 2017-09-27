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
        pt = cs->pfd.client_data;
        c->current_thread = thd;
    }

    if (c->clogging_input_filters && !c->aborted) {
        /* Since we have an input filter which 'cloggs' the input stream,
         * like mod_ssl, lets just do the normal read from input filters,
         * like the Worker MPM does.
         */
        ap_run_process_connection(c);
        if (cs->state != CONN_STATE_SUSPENDED) {
            cs->state = CONN_STATE_LINGER;
        }
    }

read_request:
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

    if (cs->state == CONN_STATE_WRITE_COMPLETION) {
        ap_filter_t *output_filter = c->output_filters;
        apr_status_t rv;
        while (output_filter->next != NULL) {
            output_filter = output_filter->next;
        }
        rv = output_filter->frec->filter_func.out_func(output_filter, NULL);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "network write failure in core output filter");
            cs->state = CONN_STATE_LINGER;
        }
        else if (c->data_in_output_filters) {
            /* Still in WRITE_COMPLETION_STATE:
             * Set a write timeout for this connection, and let the
             * event thread poll for writeability.
             */
            cs->expiration_time = ap_server_conf->timeout + apr_time_now();
            apr_thread_mutex_lock(timeout_mutex);
            APR_RING_INSERT_TAIL(&timeout_head, cs, conn_state_t, timeout_list);
            apr_thread_mutex_unlock(timeout_mutex);
            pt->bypass_push = 0;
            cs->pfd.reqevents = APR_POLLOUT | APR_POLLHUP | APR_POLLERR;
            rc = apr_pollset_add(event_pollset, &cs->pfd);
            return 1;
        }
        else if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted ||
            listener_may_exit) {
            c->cs->state = CONN_STATE_LINGER;
        }
        else if (c->data_in_input_filters) {
            cs->state = CONN_STATE_READ_REQUEST_LINE;
            goto read_request;
        }
        else {
            cs->state = CONN_STATE_CHECK_REQUEST_LINE_READABLE;
        }
    }

    if (cs->state == CONN_STATE_LINGER) {
        ap_lingering_close(c);
        apr_pool_clear(p);
        ap_push_pool(worker_queue_info, p);
        return 0;
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
        cs->expiration_time = ap_server_conf->keep_alive_timeout +
                              apr_time_now();
        apr_thread_mutex_lock(timeout_mutex);
        APR_RING_INSERT_TAIL(&keepalive_timeout_head, cs, conn_state_t, timeout_list);
        apr_thread_mutex_unlock(timeout_mutex);

        pt->bypass_push = 0;
        /* Add work to pollset. */
        cs->pfd.reqevents = APR_POLLIN;
        rc = apr_pollset_add(event_pollset, &cs->pfd);

        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                         "process_socket: apr_pollset_add failure");
            AP_DEBUG_ASSERT(rc == APR_SUCCESS);
        }
    }
    return 1;
}

/* requests_this_child has gone to zero or below.  See if the admin coded
   "MaxRequestsPerChild 0", and keep going in that case.  Doing it this way
   simplifies the hot path in worker_thread */
static void check_infinite_requests(void)
{
    if (ap_max_requests_per_child) {
        signal_threads(ST_GRACEFUL);
    }
    else {
        requests_this_child = INT_MAX;  /* keep going */
    }
}

static void unblock_signal(int sig)
{
    sigset_t sig_mask;

    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, sig);
