        apr_thread_mutex_unlock(g_timer_skiplist_mtx);

        while (num) {
            pt = (listener_poll_type *) out_pfd->client_data;
            if (pt->type == PT_CSD) {
                /* one of the sockets is readable */
                event_conn_state_t *cs = (event_conn_state_t *) pt->baton;
                struct timeout_queue *remove_from_q = cs->sc->wc_q;
                int blocking = 1;

                switch (cs->pub.state) {
                case CONN_STATE_CHECK_REQUEST_LINE_READABLE:
                    cs->pub.state = CONN_STATE_READ_REQUEST_LINE;
                    remove_from_q = cs->sc->ka_q;
                    /* don't wait for a worker for a keepalive request */
                    blocking = 0;
                    /* FALL THROUGH */
                case CONN_STATE_WRITE_COMPLETION:
                    get_worker(&have_idle_worker, blocking,
                               &workers_were_busy);
                    apr_thread_mutex_lock(timeout_mutex);
                    TO_QUEUE_REMOVE(remove_from_q, cs);
                    rc = apr_pollset_remove(event_pollset, &cs->pfd);
                    apr_thread_mutex_unlock(timeout_mutex);

                    /*
                     * Some of the pollset backends, like KQueue or Epoll
                     * automagically remove the FD if the socket is closed,
                     * therefore, we can accept _SUCCESS or _NOTFOUND,
                     * and we still want to keep going
                     */
                    if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                                     "pollset remove failed");
                        start_lingering_close_nonblocking(cs);
                        break;
                    }

                    TO_QUEUE_ELEM_INIT(cs);
                    /* If we didn't get a worker immediately for a keep-alive
                     * request, we close the connection, so that the client can
                     * re-connect to a different process.
                     */
                    if (!have_idle_worker) {
