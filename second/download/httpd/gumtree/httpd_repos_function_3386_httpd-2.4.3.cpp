static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
{
    timer_event_t *ep;
    timer_event_t *te;
    apr_status_t rc;
    proc_info *ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans;         /* Pool for per-transaction stuff */
    ap_listen_rec *lr;
    int have_idle_worker = 0;
    event_conn_state_t *cs;
    const apr_pollfd_t *out_pfd;
    apr_int32_t num = 0;
    apr_interval_time_t timeout_interval;
    apr_time_t timeout_time = 0, now, last_log;
    listener_poll_type *pt;
    int closed = 0, listeners_disabled = 0;

    last_log = apr_time_now();
    free(ti);

    /* the following times out events that are really close in the future
     *   to prevent extra poll calls
     *
     * current value is .1 second
     */
#define TIMEOUT_FUDGE_FACTOR 100000
#define EVENT_FUDGE_FACTOR 10000

    rc = init_pollset(tpool);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                     "failed to initialize pollset, "
                     "attempting to shutdown process gracefully");
        signal_threads(ST_GRACEFUL);
        return NULL;
    }

    /* Unblock the signal used to wake this thread up, and set a handler for
     * it.
     */
    unblock_signal(LISTENER_SIGNAL);
    apr_signal(LISTENER_SIGNAL, dummy_signal_handler);

    for (;;) {
        int workers_were_busy = 0;
        if (listener_may_exit) {
            close_listeners(process_slot, &closed);
            if (terminate_mode == ST_UNGRACEFUL
                || apr_atomic_read32(&connection_count) == 0)
                break;
        }

        if (conns_this_child <= 0)
            check_infinite_requests();

        now = apr_time_now();
        if (APLOGtrace6(ap_server_conf)) {
            /* trace log status every second */
            if (now - last_log > apr_time_from_msec(1000)) {
                last_log = now;
                apr_thread_mutex_lock(timeout_mutex);
                ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                             "connections: %u (clogged: %u write-completion: %d "
                             "keep-alive: %d lingering: %d suspended: %u)",
                             apr_atomic_read32(&connection_count),
                             apr_atomic_read32(&clogged_count),
                             write_completion_q.count,
                             keepalive_q.count,
                             apr_atomic_read32(&lingering_count),
                             apr_atomic_read32(&suspended_count));
                apr_thread_mutex_unlock(timeout_mutex);
            }
        }

        apr_thread_mutex_lock(g_timer_ring_mtx);
        if (!APR_RING_EMPTY(&timer_ring, timer_event_t, link)) {
            te = APR_RING_FIRST(&timer_ring);
            if (te->when > now) {
                timeout_interval = te->when - now;
            }
            else {
                timeout_interval = 1;
            }
        }
        else {
            timeout_interval = apr_time_from_msec(100);
        }
        apr_thread_mutex_unlock(g_timer_ring_mtx);

        rc = apr_pollset_poll(event_pollset, timeout_interval, &num, &out_pfd);
        if (rc != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rc)) {
                continue;
            }
            if (!APR_STATUS_IS_TIMEUP(rc)) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rc, ap_server_conf,
                             "apr_pollset_poll failed.  Attempting to "
                             "shutdown process gracefully");
                signal_threads(ST_GRACEFUL);
            }
        }

        if (listener_may_exit) {
            close_listeners(process_slot, &closed);
            if (terminate_mode == ST_UNGRACEFUL
                || apr_atomic_read32(&connection_count) == 0)
                break;
        }

        now = apr_time_now();
        apr_thread_mutex_lock(g_timer_ring_mtx);
        for (ep = APR_RING_FIRST(&timer_ring);
             ep != APR_RING_SENTINEL(&timer_ring,
                                     timer_event_t, link);
             ep = APR_RING_FIRST(&timer_ring))
        {
            if (ep->when < now + EVENT_FUDGE_FACTOR) {
                APR_RING_REMOVE(ep, link);
                push_timer2worker(ep);
            }
            else {
                break;
            }
        }
        apr_thread_mutex_unlock(g_timer_ring_mtx);

        while (num) {
            pt = (listener_poll_type *) out_pfd->client_data;
            if (pt->type == PT_CSD) {
                /* one of the sockets is readable */
                struct timeout_queue *remove_from_q = &write_completion_q;
                int blocking = 1;
                cs = (event_conn_state_t *) pt->baton;
                switch (cs->pub.state) {
                case CONN_STATE_CHECK_REQUEST_LINE_READABLE:
                    cs->pub.state = CONN_STATE_READ_REQUEST_LINE;
                    remove_from_q = &keepalive_q;
                    /* don't wait for a worker for a keepalive request */
                    blocking = 0;
                    /* FALL THROUGH */
                case CONN_STATE_WRITE_COMPLETION:
                    get_worker(&have_idle_worker, blocking,
                               &workers_were_busy);
                    apr_thread_mutex_lock(timeout_mutex);
                    TO_QUEUE_REMOVE(*remove_from_q, cs);
                    rc = apr_pollset_remove(event_pollset, &cs->pfd);

                    /*
                     * Some of the pollset backends, like KQueue or Epoll
                     * automagically remove the FD if the socket is closed,
                     * therefore, we can accept _SUCCESS or _NOTFOUND,
                     * and we still want to keep going
                     */
                    if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                                     "pollset remove failed");
                        apr_thread_mutex_unlock(timeout_mutex);
                        start_lingering_close_nonblocking(cs);
                        break;
                    }

                    apr_thread_mutex_unlock(timeout_mutex);
                    TO_QUEUE_ELEM_INIT(cs);
                    /* If we didn't get a worker immediately for a keep-alive
                     * request, we close the connection, so that the client can
                     * re-connect to a different process.
                     */
                    if (!have_idle_worker) {
                        start_lingering_close_nonblocking(cs);
                        break;
                    }
                    rc = push2worker(out_pfd, event_pollset);
                    if (rc != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                     ap_server_conf, "push2worker failed");
                    }
                    else {
                        have_idle_worker = 0;
                    }
                    break;
                case CONN_STATE_LINGER_NORMAL:
                case CONN_STATE_LINGER_SHORT:
                    process_lingering_close(cs, out_pfd);
                    break;
                default:
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                 ap_server_conf,
                                 "event_loop: unexpected state %d",
                                 cs->pub.state);
                    ap_assert(0);
                }
            }
            else if (pt->type == PT_ACCEPT) {
                /* A Listener Socket is ready for an accept() */
                if (workers_were_busy) {
                    if (!listeners_disabled)
                        disable_listensocks(process_slot);
                    listeners_disabled = 1;
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "All workers busy, not accepting new conns"
                                 "in this process");
                }
                else if (  (int)apr_atomic_read32(&connection_count)
                           - (int)apr_atomic_read32(&lingering_count)
                         > threads_per_child
                           + ap_queue_info_get_idlers(worker_queue_info) *
                             worker_factor / WORKER_FACTOR_SCALE)
                {
                    if (!listeners_disabled)
                        disable_listensocks(process_slot);
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "Too many open connections (%u), "
                                 "not accepting new conns in this process",
                                 apr_atomic_read32(&connection_count));
                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                                 "Idle workers: %u",
                                 ap_queue_info_get_idlers(worker_queue_info));
                    listeners_disabled = 1;
                }
                else if (listeners_disabled) {
                    listeners_disabled = 0;
                    enable_listensocks(process_slot);
                }
                if (!listeners_disabled) {
                    lr = (ap_listen_rec *) pt->baton;
                    ap_pop_pool(&ptrans, worker_queue_info);

                    if (ptrans == NULL) {
                        /* create a new transaction pool for each accepted socket */
                        apr_allocator_t *allocator;

                        apr_allocator_create(&allocator);
                        apr_allocator_max_free_set(allocator,
                                                   ap_max_mem_free);
                        apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
                        apr_allocator_owner_set(allocator, ptrans);
                        if (ptrans == NULL) {
                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                         ap_server_conf,
                                         "Failed to create transaction pool");
                            signal_threads(ST_GRACEFUL);
                            return NULL;
                        }
                    }
                    apr_pool_tag(ptrans, "transaction");

                    get_worker(&have_idle_worker, 1, &workers_were_busy);
                    rc = lr->accept_func(&csd, lr, ptrans);

                    /* later we trash rv and rely on csd to indicate
                     * success/failure
                     */
                    AP_DEBUG_ASSERT(rc == APR_SUCCESS || !csd);

                    if (rc == APR_EGENERAL) {
                        /* E[NM]FILE, ENOMEM, etc */
                        resource_shortage = 1;
                        signal_threads(ST_GRACEFUL);
                    }

                    if (csd != NULL) {
                        conns_this_child--;
                        rc = ap_queue_push(worker_queue, csd, NULL, ptrans);
                        if (rc != APR_SUCCESS) {
                            /* trash the connection; we couldn't queue the connected
                             * socket to a worker
                             */
                            apr_socket_close(csd);
                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                         ap_server_conf,
                                         "ap_queue_push failed");
                            apr_pool_clear(ptrans);
                            ap_push_pool(worker_queue_info, ptrans);
                        }
                        else {
                            have_idle_worker = 0;
                        }
                    }
                    else {
                        apr_pool_clear(ptrans);
                        ap_push_pool(worker_queue_info, ptrans);
                    }
                }
            }               /* if:else on pt->type */
            out_pfd++;
            num--;
        }                   /* while for processing poll */

